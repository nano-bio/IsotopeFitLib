/**
 * IsotopeFitter
 * IsotopeFitter.cpp
 * 
 * Purpose:
 * Contains the main program.
 * 
 * @author Michal Durian
 * @version 21.10.2016 15:33 MD
 * 
 * Changes log:
 * 
 */

#include "../include/IsotopeFitter.h"

using namespace std;

/* Global variables */
int fnResult;   //for function return codes

int main(int argc, char** argv)
{
    //TODO: parse argument line
    
    double fwhmRange = 0.5;     //default 0.5
    double searchRange = 1;     //default 1
    
    /* Set environment variable that sets gsl behavior */
    setenv("GSL_IEEE_MODE", "double-precision,mask-underflow,mask-denormalized", 1);
    gsl_ieee_env_setup();
    
    /* If we are compiling for release, disable the gsl default error handler. Function return codes will be used instead. */
#ifdef RELEASE
    gsl_set_error_handler_off();
#endif
    
#ifdef DEBUG
    tic();
#endif
    
    /* Load data from IFD file */
    string str = "/home/michal/Robota/IsotopeFit/IsotopeFitter/tests/finaltestfile.ifd";
    LoadIFDFile(str);
    
    /* Variable initializations needed for calibration */
    size_t dataLength = IFData::RawData[0].size();
    size_t moleculeCount = IFData::MoleculesData.size();
     
    vector<double> Signal(dataLength);
    vector<double> MassAxis(dataLength);
        
    vector<double> ResolutionFitCoefs(3);
        
#ifdef DEBUG
    toc("start - end of init");
#endif    
    
#ifdef DEBUG
    tic();
#endif

    /* Background correction */
    CorrectBaseline(IFData::BGCorrectionData, IFData::RawData, Signal);
    
#ifdef DEBUG
    toc("baseline fit with subtraction");
#endif
    
#ifdef DEBUG
    tic();
#endif
    
    /* Mass offset correction */
    CorrectMassOffsets(IFData::CalibrationData, IFData::RawData[0], MassAxis);
    
    /* Refresh dataLength in case the massa axis got cropped during the mass axis correction. No need to crop the signal vector, because it is accessed using the dataLength. */
    dataLength = MassAxis.size();
    
#ifdef DEBUG
    toc("fit mass offset");
#endif    
    
#ifdef DEBUG
    tic();
#endif
    
    /* Resolution fit */
    FitResolution(IFData::CalibrationData, ResolutionFitCoefs);
    
#ifdef DEBUG
    toc("fit resolution");
#endif
        
#ifdef DEBUG
    tic();
#endif
    
    /* Initialization of variables needed in the design matrix build loop */

    gsl_spmatrix *Design_m = gsl_spmatrix_alloc(dataLength, moleculeCount);    
    gsl_spmatrix_set_zero(Design_m);
    
    gsl_spmatrix *DesignTemp_m = gsl_spmatrix_alloc(dataLength, moleculeCount);
    gsl_spmatrix_set_zero(DesignTemp_m);
    
    vector<bool> FitMask(dataLength);
    fill(FitMask.begin(), FitMask.end(), false);
    
    int peakLowerLimitIndex, peakUpperLimitIndex, fitmaskLowerLimitIndex, fitmaskUpperLimitIndex, breakIndex;
    double mass, area, resolution, fwhm, idealSignalValue;
    
    vector<double> BreaksRecalc(IFData::CalibrationData.Shape.Breaks.size()); 
    
    gsl_matrix *ShapeCoefsRecalc_m = gsl_matrix_alloc(IFData::CalibrationData.Shape.Coefs.size(), IFData::CalibrationData.Shape.Coefs[0].size());
    gsl_vector_view ShapeCoefsRow;
    double ShapeCoefsRowArr[4]; //4 is hardcoded, because it expects four coefficients for a cubic spline
    
#ifdef DEBUG
    toc("inits before molecule loop");
#endif
    
#ifdef DEBUG
    ticloop();
#endif
    
    /* Design matrix build loop. Loop through all molecules. */
    cout << moleculeCount << endl;
    for (int i = 0; i < moleculeCount; i++)
    {
        /* Loop through isotope peaks of current molecule */
        for (int j = 0; j < IFData::MoleculesData[i].PeakData.size(); j++)
        {
            
#ifdef DEBUG
    if (i==0 && j==0) tic();
#endif
    
            /* Read mass and area of current isotope peak */
            mass = IFData::MoleculesData[i].PeakData[j][0];
            area = IFData::MoleculesData[i].PeakData[j][1];
            
            /* Calculate resolution of the line from resolution fit parameters. */
            //TODO: 3 is hardcoded, it will be read from calibration data later
            resolution = gsl_poly_eval(ResolutionFitCoefs.data(), 3, mass);
            
            fwhm = mass / resolution;
            
            /* Check if it is negative */
            if (fwhm < 0)
            {
                //TODO: reorder breaks and coefs? check matlab code
                cout << "fwhm negative " << fwhm << endl;
            }
            
#ifdef DEBUG
    if (i==0 && j==0) toc("molecule loop 1");
#endif            
            
#ifdef DEBUG
    if (i==0 && j==0) tic();
#endif
            
            /* Shape breaks transformation. */            
            TransformShapeBreaks(IFData::CalibrationData, fwhm, mass, BreaksRecalc);
            
#ifdef DEBUG
    if (i==0 && j==0) toc("breaksrecalc");
#endif
            
#ifdef DEBUG
    if (i==0 && j==0) tic();
#endif
            
            /* Shape coefficient transformation. */            
            TransformShapeCoefs(IFData::CalibrationData, fwhm, area, ShapeCoefsRecalc_m);
       
#ifdef DEBUG
    if (i==0 && j==0) toc("coefsrecalc");
#endif  
            
#ifdef DEBUG
    if (i==0 && j==0) tic();
#endif
      
            /* Find peak and fitmask limits. */
            peakLowerLimitIndex = FindLowerLimitIndex(MassAxis, BreaksRecalc.front());            
            peakUpperLimitIndex = FindUpperLimitIndex(MassAxis, BreaksRecalc.back());            
            fitmaskLowerLimitIndex = FindLowerLimitIndex(MassAxis, mass - searchRange * fwhmRange * fwhm);
            fitmaskUpperLimitIndex = FindUpperLimitIndex(MassAxis, mass + searchRange * fwhmRange * fwhm);
            
#ifdef DEBUG
    if (i==0 && j==0) toc("peak and fitmask limits");
#endif            
            
#ifdef DEBUG
    if (i==0 && j==0) tic();
#endif

            /* Adjust the fitmask. This is done cumulatively. */
            for(int k = fitmaskLowerLimitIndex; k <= fitmaskUpperLimitIndex; k++)
            {
                FitMask[k] = true;
            }
            
#ifdef DEBUG
    if (i==0 && j==0) toc("Fitmask");
#endif 
            
#ifdef DEBUG
    if (i==0 && j==0) tic();
#endif
            
            /* Build design matrix */
            
            /* Important to erase data from previous iteration. */
            gsl_spmatrix_set_zero(DesignTemp_m);
                        
            for(int k = peakLowerLimitIndex; k <= peakUpperLimitIndex; k++)
            {
                /* evaluate the peakshape partial polynomial at the k index of mass axis */
                
                breakIndex = 1; //it is ok to start at 1, because peakLowerLimitIndex is the index of break 0
                
                do
                {                    
                    if(MassAxis[k] < BreaksRecalc[breakIndex])  //the point on mass axis belongs to currently evaluated partial polynomial
                    {
                        /* evaluate the correct partial polynomial */
                        ShapeCoefsRow = gsl_matrix_row(ShapeCoefsRecalc_m, breakIndex - 1);
                        
                        /* This is done because gsl_poly_eval takes polynomial coefficients in reversed order than matlab. */
                        for(int l = 0; l < 4; l++)
                        {
                            ShapeCoefsRowArr[l] = gsl_vector_get(&ShapeCoefsRow.vector, l);
                        }
                        
                        reverse(std::begin(ShapeCoefsRowArr), std::end(ShapeCoefsRowArr));
                        
                        idealSignalValue = area * gsl_poly_eval(ShapeCoefsRowArr, 4, MassAxis[k] - BreaksRecalc[breakIndex - 1]);
                        break;
                    }
                    else    //move on to next partial polynomial
                    {
                        breakIndex++;
                    }
                }while(breakIndex < BreaksRecalc.size());
                
                /* set the partial design matrix, if the point is in fitmask */
                //TODO: we can use the fitmask boundaries in the calculation of the ideal signal, it will be even faster
                //TODO: fix the masking - the values should be removed
                if (FitMask[k])
                {
                    gsl_spmatrix_set(DesignTemp_m, k, i, idealSignalValue);
                }
            }
#ifdef DEBUG
    if (i==0 && j==0) toc("build M_temp");
#endif            
            
#ifdef DEBUG
    if (i==0 && j==0) tic();
#endif
            
            /* add the partial matrix to the final one */
            int nonZeroCount = DesignTemp_m->nz;
            
            for (int k = 0; k < nonZeroCount; k++)
            {
                /* there is no addition operation itself, because the accessed values of M should be zero anyway */
                gsl_spmatrix_set(Design_m, DesignTemp_m->i[k], DesignTemp_m->p[k], DesignTemp_m->data[k]);
            }
            
#ifdef DEBUG
    if (i==0 && j==0) toc("add");
#endif            
        }
    }
    
    /* Cleanup after the design matrix build loop. */
    gsl_spmatrix_free(DesignTemp_m);
    gsl_matrix_free(ShapeCoefsRecalc_m);
    
#ifdef DEBUG
    tocloop("molecule loop");
#endif    
    
#ifdef DEBUG
    tic();
#endif

    /* Apply fitmask to signal */
    //TODO: this can be maybe optimized
    //TODO: fix the masking - the values should be removed
    for (int i = 0; i < dataLength; i++)
    {
        if(!FitMask[i])
        {            
            Signal[i] = 0;
        }
    }
    
#ifdef DEBUG
    toc("apply fitmask");
#endif
    
    /* Initialize the linear squares solver system */
    gsl_multilarge_linear_workspace *WrkSpc = gsl_multilarge_linear_alloc(gsl_multilarge_linear_tsqr, moleculeCount);
        
    /* Regularization matrix. It is initialized as a vector, because the matrix is diagonal. */
    gsl_vector *Regularization_v = gsl_vector_alloc(moleculeCount);
    for (int i=0; i<moleculeCount; i++)
    {
        gsl_vector_set(Regularization_v, i, 1);
    }
    
#ifdef DEBUG
    tic();
#endif
    
    /* Convert the sparse design matrix into a dense one. Required by the solver functions. */
    gsl_matrix *Design_mDens = gsl_matrix_alloc(dataLength, moleculeCount);
    gsl_spmatrix_sp2d(Design_mDens, Design_m);
    
#ifdef DEBUG
    toc("to dense");
#endif
    
#ifdef DEBUG
    tic();
#endif
    
    /* Copy Signal data in to a gsl vector. Required by gsl functions. Can and will be optimized. */
    //TODO: output as gsl vector from the resfit routine, then save this step
    gsl_vector *Signal_v = gsl_vector_alloc(dataLength);
    for (int i = 0; i < dataLength; i++)
    {
        gsl_vector_set(Signal_v, i, Signal[i]);
    }
    
#ifdef DEBUG
    toc("copy signal");
#endif
    
#ifdef DEBUG
    ticloop();
#endif
    
    /* Add data to the linear solver workspace. This has to be done by pieces. */    
    
    /* Submatrix of the design matrix and signal subvector */
    gsl_matrix_view DesignSub;
    gsl_vector_view SignalSub;
    
    /* Standard form of the submatrix and subvector */
    gsl_matrix *DesignSubStd_m;
    gsl_vector *SignalSubStd_v;
    
    int blockIndex = 0;
    int rowsLeft = dataLength;    
    int blockSize = moleculeCount;  //size of one block to accumulate, num of row
    
    /* Loop runs until all rows from the design matrix are read. */
    do
    {      
        
#ifdef DEBUG
    tic();
#endif
    
        if(rowsLeft > blockSize)    //TODO: was moleculeCount, but this should be correct
        {
            /* Get submatrix and subvector from design matrix and signal vector */
            DesignSub = gsl_matrix_submatrix(Design_mDens, blockIndex * blockSize, 0, blockSize, moleculeCount);
            SignalSub = gsl_vector_subvector(Signal_v, blockIndex * blockSize, blockSize);
            
            DesignSubStd_m = gsl_matrix_alloc(DesignSub.matrix.size1, DesignSub.matrix.size2);
            SignalSubStd_v = gsl_vector_alloc(SignalSub.vector.size);
            
            /* Keep track of how many rows we still have to read */
            rowsLeft -= blockSize;
        }
        else
        {
            /* Get submatrix and subvector from design matrix and signal vector */
            DesignSub = gsl_matrix_submatrix(Design_mDens, blockIndex * blockSize, 0, rowsLeft, moleculeCount);
            SignalSub = gsl_vector_subvector(Signal_v, blockIndex * blockSize, rowsLeft);
            
            DesignSubStd_m = gsl_matrix_alloc(DesignSub.matrix.size1, DesignSub.matrix.size2);
            SignalSubStd_v = gsl_vector_alloc(SignalSub.vector.size);
            
            rowsLeft = 0;
        }
    
        /* Transform to standard form using the regularization matrix. */
        gsl_multilarge_linear_stdform1(Regularization_v, &DesignSub.matrix, &SignalSub.vector, DesignSubStd_m, SignalSubStd_v, WrkSpc);
            
        /* Add the block to the solver */
        gsl_multilarge_linear_accumulate(DesignSubStd_m, SignalSubStd_v, WrkSpc);
        
        blockIndex++;
        
#ifdef DEBUG
    toc("transform + accumulate iteration");
#endif

    }while(rowsLeft > 0);
    
#ifdef DEBUG
    tocloop("transform + accumulate loop");
#endif
 
#ifdef DEBUG
    tic();
#endif 
    
    /* Calculate optimal regularization parameter for the current system. */
    double regParam = GetOptimalRegParam(WrkSpc);
        
#ifdef DEBUG
    toc("regparam");
#endif   
    
#ifdef DEBUG
    tic();
#endif
    
    /* Solve the system */
    gsl_vector *LSqrSolutionStd_v = gsl_vector_alloc(moleculeCount);
    double resNorm, solNorm;
    
    int fnResult = gsl_multilarge_linear_solve(regParam, LSqrSolutionStd_v, &resNorm, &solNorm, WrkSpc); //gsl_vector_get(RegParams2_v, regParIndex)
    
    if(fnResult != 0)
    {
        //TODO: error
    }
    
#ifdef DEBUG
    toc("solve");
#endif
    
    /* Transform the solution back to general form */
    gsl_vector *SignalCalc_v = gsl_vector_alloc(moleculeCount);
    gsl_multilarge_linear_genform1(Regularization_v, LSqrSolutionStd_v, SignalCalc_v, WrkSpc);
    
    /* Outputs the solution vector to console. */
//    for (int i = 0; i < moleculeCount; i++)
//    {
//        cout << gsl_vector_get(SignalCalc_v, i) << endl;
//    }
    
#ifdef DEBUG
    tic();
#endif
    
    /* Calculate the fitted spectrum */
    gsl_vector *CalcSignal = gsl_vector_alloc(dataLength);
    gsl_blas_dgemv(CblasNoTrans, 1, Design_mDens, SignalCalc_v, 0, CalcSignal);
    
#ifdef DEBUG
    toc("calc spectrum");
#endif
    
    /* Outputs */
    cout << "rnorm " << resNorm << endl;
    cout << "snorm " << solNorm << endl;
    
    /* Calculated signal is written to a text file. */
    ofstream calcSpec;
    calcSpec.open("calcSpec");
    for (int i = 0; i < dataLength; i++)
    {
        calcSpec << MassAxis[i] << " " << gsl_vector_get(CalcSignal, i) << " " << Signal[i] << endl;
    }
    calcSpec.close();
    
    return EXIT_SUCCESS;
}