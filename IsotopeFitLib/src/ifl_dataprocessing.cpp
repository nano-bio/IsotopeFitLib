/**
 * IsotopeFitLib
 * ifl_dataprocessing.cpp
 * 
 * @author Michal Durian
 * @version 17.10.2016 12:52 MD
 * 
 * Changes log:
 * 
 */

#include "../include/ifl_dataprocessing.h"

using namespace std;

/* Functions definitions */

void CropData()
{
    //TODO: check matlab code
}

/**
 * Fits background correction data, calculates baseline and subtracts it from raw signal.
 * It still needs more fitting methods and also safer and saner way of extrapolating.
 * 
 * @param BGCorrData - Struct containing background correction data, extracted previously from IFD file.
 * @param &RawData - Vector containing raw mass axis and raw signal.
 * @param &OutCorrSignal - Vector, which will be filled with corrected signal.
 */
void CorrectBaseline(const BGCorrection_t BGCorrData, const vector<vector<double> > &RawData, vector<double> &OutCorrSignal)
{
    /* Initialize some sizes */
    size_t massAxisSize = RawData[0].size();
    size_t fitDataLength = BGCorrData.Bgm.size();
    
    /* Initialize the fitting routine */
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *spline = gsl_spline_alloc (gsl_interp_steffen, fitDataLength);   //TODO: more interpolation types
    
    /* Run the fit */
    int result = gsl_spline_init (spline, BGCorrData.Bgm.data(), BGCorrData.Bgy.data(), fitDataLength);    
    
    /* Check for errors */
    if(result != 0)
    {
        //TODO: throw
    }
    
    /* Evaluate the fitted function and write to output. Uses hack to allow for extrapolation. */
    for (int i = 0; i < massAxisSize; i++) //xInterp = MassAxis[0]; xInterp < massaxis[masaxsize-1]; xInterp += 10
    {
        spline->interp->type->eval(spline->interp->state, BGCorrData.Bgm.data(), BGCorrData.Bgy.data(), spline->interp->size, RawData[0][i], acc, &OutCorrSignal[i]);
        OutCorrSignal[i] = RawData[1][i] - OutCorrSignal[i];
    }    
    
    /* Free the resources */
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
}

/**
 * Fits calibration data to provide mass offset correction of mass axis.
 * 
 * @param CalData - Struct containing calibration data, extracted previously from IFD file.
 * @param &InMassAxis - Vector containing uncorrected mass axis.
 * @param &OutMassAxisCorr - Vector, which will be filled with corrected mass axis.
 */
void CorrectMassOffsets(const Calibration_t CalData, const vector<double> &RawMassAxis, vector<double> &OutMassAxisCorr)
{
    /* right now the method parameter is ignored. steffen spline fit is performed. */
    
    size_t massAxisSize = RawMassAxis.size();
    size_t fitDataLength = CalData.COMList.size();
    
    /* Generate x-axis for the fit */    
    auto minMax = minmax_element(RawMassAxis.begin(), RawMassAxis.end());
    double XAxisMin = RawMassAxis[minMax.first - RawMassAxis.begin()];
    double XAxisMax = RawMassAxis[minMax.second - RawMassAxis.begin()];

    size_t XAxisSize = (XAxisMax - XAxisMin) / 0.01;
    vector<double> XAxis;
    XAxis.resize(XAxisSize);
    
    for (int i = 0; i < XAxisSize; i++)
    {
        XAxis[i] = XAxisMin + i * 0.01;
    }
    
    /* Will hold evaluated data from the first fit and serve as x-axis (yes, x-axis) in the second fit. Because the fit needs to be reversed. */
    vector<double> YAxis;
    YAxis.resize(XAxisSize);
    
    /* Fit of calibration data */
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *spline = gsl_spline_alloc (gsl_interp_steffen, fitDataLength);
    int result = gsl_spline_init (spline, CalData.COMList.data(), CalData.MassOffsetList.data(), fitDataLength);
    
    //TODO: success check
    
    /* Evaluation of the fit at positions given by generated x-axis and storing the correction in YAxis vector. */
    for (int i = 0; i < XAxisSize; i++)
    {
        //TODO: maybe can be written without the extrapolation hack
        spline->interp->type->eval(spline->interp->state, CalData.COMList.data(), CalData.MassOffsetList.data(), spline->interp->size, XAxis[i], acc, &YAxis[i]);
        YAxis[i] += XAxis[i];
    }
    
    /* Free resources from the first fit */
    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
    
    /* This is a sanity check for YAxis monotonicity. That is required by the second fit, where the YAxis server as x-axis. Matlab does this without telling.
     * This could be solved in a more safe way, if the user would actually specify endindex of the raw data, so the uncalibrated range can get cut out. */
    auto Max = max_element(YAxis.begin(), YAxis.end());
    YAxis.erase(Max, YAxis.end());
    size_t yAxisSize = YAxis.size();    
    
    /* Fit to generate corrected mass axis. Note that the X and Y axis are inverted. For this to be correct, it must be corrected in the IFD file generation first. */
    gsl_interp_accel *acc2 = gsl_interp_accel_alloc ();
    gsl_spline *spline2 = gsl_spline_alloc (gsl_interp_steffen, yAxisSize);
    int result2 = gsl_spline_init (spline, YAxis.data(), XAxis.data(), yAxisSize);
    //TODO: success check
    
    /* Evaluation of the secod fit, with results written to the output vector. */
    for (int i = 0; RawMassAxis[i] < YAxis[yAxisSize - 1]; i++)
    {
        //TODO: maybe can be written without the extrapolation hack
        spline->interp->type->eval(spline->interp->state, YAxis.data(), XAxis.data(), spline->interp->size, RawMassAxis[i], acc, &OutMassAxisCorr[i]);
    }
    
    /* It might happen due to the monotonicity check, that during the second evaluation we hit a singularity. This cuts off the nonsense data. */
    Max = max_element(OutMassAxisCorr.begin(), OutMassAxisCorr.end());
    OutMassAxisCorr.erase(Max, OutMassAxisCorr.end());
    
    /* free resources from the second fit */
    gsl_spline_free (spline2);
    gsl_interp_accel_free (acc2);
}

/* Fits the resolution quadratically: y = c0 + c1 * x + c2 * x^2 */
  //TODO: make enum for the fit method

/**
 * Fits calibration data to provide mass offset correction of mass axis.
 * 
 * @param CalData - Struct containing calibration data, extracted previously from IFD file.
 * @param &OutFitCoefs - Vector, which will be filled with calculated fit coefficients.
 */
void FitResolution(const Calibration_t CalData, vector<double> &OutFitCoefs)
{
    /* right now the method parameter is ignored. quadratic fit is performed. */
    
    //TODO: generalize for arbitrary order polynomial
    //TODO: add more fit methods
    
    /* Get length of input data */
    size_t fitDataLength = CalData.COMList.size();  //TODO: include a check if their sizes are equal?
    
    /* Will contain residual values after the fit */
    double residual;
    
    /* Check if the output vector is correctly preallocated */
    if(OutFitCoefs.size() != 3)
    {
        //TODO: throw
    }
    
    /* Fit everything into gsl containers */
    gsl_matrix *COMList_m = gsl_matrix_alloc(fitDataLength, 3);
    gsl_vector *ResList_v = gsl_vector_alloc(fitDataLength);
    gsl_vector *Coefs_v = gsl_vector_alloc(3);
    gsl_matrix *Covariance_m = gsl_matrix_alloc(3, 3);     //not used after the fit at the moment
    
    for(int i = 0; i < fitDataLength; i++)
    {
        gsl_matrix_set(COMList_m, i, 0, 1);
        gsl_matrix_set(COMList_m, i, 1, CalData.COMList[i]);
        gsl_matrix_set(COMList_m, i, 2, CalData.COMList[i] * CalData.COMList[i]);
        
        gsl_vector_set(ResList_v, i, CalData.ResolutionList[i]);
    }    
    
    /* Fit */
    gsl_multifit_linear_workspace *Wrk = gsl_multifit_linear_alloc(fitDataLength, 3);
    gsl_multifit_linear(COMList_m, ResList_v, Coefs_v, Covariance_m, &residual, Wrk);
    gsl_multifit_linear_free(Wrk);
    
    /* Success check */
    //TODO: success check
    
    /* Copy calculated coefficients to output vector */
    for (int i = 0; i < 3; i++)
    {
        OutFitCoefs[i] = gsl_vector_get(Coefs_v, i);
    }
}

//void FitBaseline(const vector<double> &BgMass, const vector<double> &BgY, const vector<double> &MassAxis, vector<double> &OutBaseline)
//{
//    //TODO: outbaseline must be initialized and with proper size
//    
////    double *massaxis = &IFData::RawData[0][0];    
//    size_t massAxisSize = MassAxis.size();
//    
//    //cout << massaxis[0] << " " << massaxis[masaxsize-1] << endl;
//    
////    double *bgm = &IFData::BGCorrectionData.Bgm[0];
////    double *bgy = &IFData::BGCorrectionData.Bgy[0];
//    size_t fitDataLength = BgMass.size();
//    
//    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
//    gsl_spline *spline = gsl_spline_alloc (gsl_interp_steffen, fitDataLength);   //TODO: more interpolation types
//    int result = gsl_spline_init (spline, BgMass.data(), BgY.data(), fitDataLength);    
//    
//    //cout << "bgcorr fit res " << result << endl;
//    
//    //double xInterp;
//    
//    for (int i = 0; i < massAxisSize; i++) //xInterp = MassAxis[0]; xInterp < massaxis[masaxsize-1]; xInterp += 10
//    {
//        //yi = gsl_spline_eval (spline, xi, acc);
//        spline->interp->type->eval(spline->interp->state, BgMass.data(), BgY.data(), spline->interp->size, MassAxis[i], acc, &OutBaseline[i]);
//    }
//    
//    
//    for (int i = 0; i < Signal.size(); i++)
//    {
//        Signal[i] = IFData::RawData[1][i] - Baseline[i];
//    }
    
    //TODO: subtract the evaluated curve from rawdata
    
    //TODO: free resources
//}