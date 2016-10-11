/* Headers */
#include "../include/fitting.h"

#include <vector>

/* Namespaces */
using namespace std;

/* Functions definitions */

/* Fits the resolution linearly: y = c0 + c1 * x */
void FitResolution(const vector<double> &COMList, const vector<double> &ResolutionList, const int &method, double &outC0, double &outC1)   //TODO: make enum for the fit method
{
    /* right now the method parameter is ignored. linear fit is performed. */
    
    size_t fitDataLength = COMList.size();  //TODO: include a check if their sizes are equal?
    
    double cov00, cov01, cov11, sumsq;  //they are not used further at the moment
    
    /* Fit function, returns 0 if successful. */
    int result = gsl_fit_linear(COMList.data(), 1, ResolutionList.data(), 1, fitDataLength, &outC0, &outC1, &cov00, &cov01, &cov11, &sumsq);
    
    cout << "fit resoultion result " << result << endl;
    
    /* success check */
//    if (result != 0)
//    {
//        //TODO: exception
//        cout << "fit resoultion result " << result << endl;
//    }
}

/* fits mass offset with steffen spline */
void FitMassOffsets(const vector<double> &COMList, const vector<double> &MassOffsetList, const int &method, const vector<double> &MassAxis, vector<double> &MassAxisCorr)
{
    /* right now the method parameter is ignored. steffen spline fit is performed. */
    
    size_t massAxisSize = MassAxis.size();
//    double *x_comlist = &IFData::CalibrationData.COMList[0];
//    double *y_massofset = &IFData::CalibrationData.MassOffsetList[0];
    size_t fitDataLength = COMList.size();
    
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *spline = gsl_spline_alloc (gsl_interp_steffen, fitDataLength);   //gsl_interp_cspline
    int result = gsl_spline_init (spline, COMList.data(), MassOffsetList.data(), fitDataLength);
    
    cout << "mass ofset fit result " << result << endl;
    
    for (int i = 0; i < massAxisSize; i++)
    {
        spline->interp->type->eval(spline->interp->state, COMList.data(), MassOffsetList.data(), spline->interp->size, MassAxis[i], acc, &MassAxisCorr[i]);
        //TODO: forgot to subtract
    }
    
    //TODO: free resources
    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
}

/**
 * Fits background correction data and outputs a baseline
 * 
 * @param &BgMass Pointer to the background correction x-axis data extracted from IFD file.
 * TODO
 */
void FitBaseline(const vector<double> &BgMass, const vector<double> &BgY, const vector<double> &MassAxis, vector<double> &OutBaseline)
{
    //TODO: outbaseline must be initialized and with proper size
    
//    double *massaxis = &IFData::RawData[0][0];    
    size_t massAxisSize = MassAxis.size();
    
    //cout << massaxis[0] << " " << massaxis[masaxsize-1] << endl;
    
//    double *bgm = &IFData::BGCorrectionData.Bgm[0];
//    double *bgy = &IFData::BGCorrectionData.Bgy[0];
    size_t fitDataLength = BgMass.size();
    
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *spline = gsl_spline_alloc (gsl_interp_steffen, fitDataLength);   //TODO: more interpolation types
    int result = gsl_spline_init (spline, BgMass.data(), BgY.data(), fitDataLength);    
    
    cout << "bgcorr fit res " << result << endl;
    
    //double xInterp;
    
    for (int i = 0; i < massAxisSize; i++) //xInterp = MassAxis[0]; xInterp < massaxis[masaxsize-1]; xInterp += 10
    {
        //yi = gsl_spline_eval (spline, xi, acc);
        spline->interp->type->eval(spline->interp->state, BgMass.data(), BgY.data(), spline->interp->size, MassAxis[i], acc, &OutBaseline[i]);
    }
    
    //TODO: subtract the evaluated curve from rawdata
    
    //TODO: free resources
}

void CropData()
{
    
}

void FitCalibration()
{
    
}