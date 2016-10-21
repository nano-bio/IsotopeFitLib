#include <stdlib.h>
#include <iostream>

#include <algorithm>

#include "src/IsotopeFitter.h"  //TODO: move the header to include folder

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_multilarge.h>




using namespace std;

void test1() {
    std::cout << "fittingtest2 test 1" << std::endl;
            
    /* Load data from IFD file */
    string str = "/home/matlab/Michal/dev/IsotopeFitter/tests/testfileifd2.ifd";
    LoadIFDFile(str);
    
    /* Variable initializations */
    vector<double> Baseline, Signal, MassAxis;
    //double resPar0, resPar1;
    double resPar[2];
    
    size_t dataLength = IFData::RawData[0].size();
    size_t moleculeCount = IFData::MoleculesData.size();
    
    Baseline.resize(dataLength);
    Signal.resize(dataLength);
    MassAxis.resize(dataLength);
    
    /* Background correction */
    FitBaseline(IFData::BGCorrectionData.Bgm, IFData::BGCorrectionData.Bgy, IFData::RawData[0], Baseline);
    
    /* Actual subtraction of the baseline */
    //TODO: this can be done inside the baseline function
    for (int i = 0; i < Signal.size(); i++)
    {
        Signal[i] = IFData::RawData[1][i] - Baseline[i];
    }

    /* Mass offset correction */
    FitMassOffsets(IFData::CalibrationData.COMList, IFData::CalibrationData.MassOffsetList, 0, IFData::RawData[0], MassAxis);
          
    /* Resolution fit */
    FitResolution(IFData::CalibrationData.COMList, IFData::CalibrationData.ResolutionList, 0, resPar[0], resPar[1]);
    
    /* Design matrix initialization */
    gsl_spmatrix *M = gsl_spmatrix_alloc(dataLength, moleculeCount);    
    
    gsl_spmatrix_set_zero(M);
    //M = gsl_spmatrix_ccs(M);  //TODO: try also with crs
    
    /* Fitmask initialization */
    vector<bool> Fitmask;
    Fitmask.resize(dataLength);
    fill(Fitmask.begin(), Fitmask.end(), false);
    
    //TODO: why?
    double fwhmrange = 0.5;
    double searchrange = 1;
    
    /* Variables used in the loop */
    double mass, area, R, fwhm, idealSignalValue;
    vector<double> Breaks, BreaksRecalc;
    int peakLowerLimitIndex, peakUpperLimitIndex, fitmaskLowerLimitIndex, fitmaskUpperLimitIndex, breakIndex;
//    gsl_matrix *Coefs, *CoefsRecalc;
    
//    Breaks.resize(IFData::CalibrationData.Shape.Breaks.size());
//    Coefs.resize(IFData::CalibrationData.Shape.Coefs.size());
    
    Breaks = IFData::CalibrationData.Shape.Breaks;
    BreaksRecalc.resize(IFData::CalibrationData.Shape.Breaks.size());
    
//    Coefs = IFData::CalibrationData.Shape.Coefs;    
//    CoefsRecalc = IFData::CalibrationData.Shape.Coefs;  //easier than resizing the matrix
    //for_each(CoefsRecalc.begin(), CoefsRecalc.end(), vector.resize(IFData::CalibrationData.Shape.Coefs[0].size()));
    
    /* Load coefs into matrix */
    gsl_matrix *Coefs = gsl_matrix_alloc(IFData::CalibrationData.Shape.Coefs.size(), IFData::CalibrationData.Shape.Coefs[0].size());
    gsl_matrix *CoefsRecalc = gsl_matrix_alloc(IFData::CalibrationData.Shape.Coefs.size(), IFData::CalibrationData.Shape.Coefs[0].size());
    
    gsl_vector_view CoefsRow;
    
    for (int j=0; j<IFData::CalibrationData.Shape.Coefs.size(); j++)
    {
        for (int k=0; k<IFData::CalibrationData.Shape.Coefs[j].size(); k++)
        {
            gsl_matrix_set(Coefs, j, k, IFData::CalibrationData.Shape.Coefs[j][k]);
        }
    }
    
//    cout << "check" << endl;
    
    /* Loop through all molecules */
    for (int i = 0; i < moleculeCount; i++)
    {
        /* Loop through isotope peaks of current molecule */
        for (int j = 0; j < IFData::MoleculesData[i].PeakData.size(); j++)
        {
            mass = IFData::MoleculesData[i].PeakData[j][0];
            area = IFData::MoleculesData[i].PeakData[j][1];
            
            /* Calculate resolution of the line from resolution fit parameters, depending on its mass. 2 is hardcoded, because the fit is linear at the moment. */
            R = gsl_poly_eval(resPar, 2, mass);
            
            fwhm = mass / R;
            
            if (fwhm < 0)
            {
                cout << "fwhm negative " << fwhm << endl;
            }
            
            /* Shape recalculation. This will go to the library later. */
            
            //transform(Breaks.begin(), Breaks.end(), Breaks.begin(), [](double x){return x * mass / R;});
            
            for(int k = 0; k < IFData::CalibrationData.Shape.Breaks.size(); k++)
            {
                BreaksRecalc[k] = Breaks[k] * fwhm + mass;
            }
            
//            cout << IFData::CalibrationData.Shape.Coefs.size() << " " << IFData::CalibrationData.Shape.Coefs[0].size() << endl;
            
            for (int l = 0; l < IFData::CalibrationData.Shape.Coefs.size(); l++)
            {
//                cout << "check " << l << endl;
                for (int k=0; k<IFData::CalibrationData.Shape.Coefs[l].size(); k++)
                {                    
                    switch(k % 4)
                    {
                        case 0 :
                        {
                            gsl_matrix_set(CoefsRecalc, l, k, gsl_matrix_get(Coefs, l, k) / gsl_pow_3(fwhm));
                            break;
                        }
                        case 1 :
                        {
                            gsl_matrix_set(CoefsRecalc, l, k, gsl_matrix_get(Coefs, l, k) / gsl_pow_2(fwhm));
                            break;
                        }
                        case 2 :
                        {
                            gsl_matrix_set(CoefsRecalc, l, k, gsl_matrix_get(Coefs, l, k) / fwhm);
                            break;
                        }
                        case 3 :
                        {
                            gsl_matrix_set(CoefsRecalc, l, k, gsl_matrix_get(Coefs, l, k));
                            break;
                        }
                    }
                    
                    /* Area normalization */
                    //gsl_matrix_set(CoefsRecalc, l, k, gsl_matrix_get(CoefsRecalc, l, k) * area / fwhm);
                    //gsl_matrix_set(Coefs, l, k, CoefsRecalc);
                }                
            }
            
            /* find indices on the massaxis, where elements are within the range of breaks. Might be relocated elsewhere. */
            for(int k = 0; k < MassAxis.size(); k++)
            {
                if(MassAxis[k] < BreaksRecalc[0])
                {
                    peakLowerLimitIndex = k;    //might actually be slightly outside the breaks range -> extrapolate or +1
                }
                else break;
            }
            
            for(int k = MassAxis.size() - 1; k >= 0; k--)
            {
                if(MassAxis[k] > BreaksRecalc[BreaksRecalc.size() - 1])
                {
                    peakUpperLimitIndex = k;
                }
                else break;
            }
            
//            cout << peakLowerLimitIndex << " " << peakUpperLimitIndex << endl;
            
            /* find indices on the massaxis, where elements are within the search range. */
            for(int k = 0; k < MassAxis.size(); k++)
            {
                if(MassAxis[k] < mass - searchrange * fwhmrange * fwhm)
                {
                    fitmaskLowerLimitIndex = k;
                }
                else break;
            }
            
            for(int k = MassAxis.size() - 1; k >= 0; k--)
            {
                if(MassAxis[k] > mass + searchrange * fwhmrange * fwhm)
                {
                    fitmaskUpperLimitIndex = k;
                }
                else break;
            }
            
//            cout << fitmaskLowerLimitIndex << " " << fitmaskUpperLimitIndex << endl;
            
            /* Adjust the fitmask. This is done cumulatively. */
            for(int k = 0; k < Fitmask.size(); k++)
            {
                if(k >= fitmaskLowerLimitIndex && k <= fitmaskUpperLimitIndex)
                {
                    Fitmask[k] = true;
                }
            }
            
            /* Build design matrix */
            gsl_spmatrix *M_temp = gsl_spmatrix_alloc(dataLength, moleculeCount);
            
            for(int k = peakLowerLimitIndex; k < peakUpperLimitIndex; k++)
            {
                /* evaluate the peakshape partial polynomial at the k index of mass axis */
                breakIndex = 1; //it is ok to start at 1, because peakLowerLimitIndex it the index of break 0
                
                do
                {                    
                    if(MassAxis[k] < BreaksRecalc[breakIndex])
                    {
                        /* evaluate the correct partial polynomial */
                        CoefsRow = gsl_matrix_row(CoefsRecalc, breakIndex - 1);
                        
                        idealSignalValue = gsl_poly_eval(gsl_vector_ptr(&CoefsRow.vector, 0), 4, MassAxis[k]);
                        break;
                    }
                    else
                    {
//                        if(breakIndex == BreaksRecalc.size() - 1)   //segfault protection, for the last peakshape segment
//                        {
//                            CoefsRow = gsl_matrix_row(CoefsRecalc, breakIndex - 1);
//                        
//                            idealSignalValue = gsl_poly_eval(gsl_vector_ptr(&CoefsRow.vector, 0), 4, MassAxis[k]);
//                            break;
//                        }
//                        else
//                        {
//                            breakIndex++;
//                        }

                        breakIndex++;
                    }
                }while(breakIndex < BreaksRecalc.size());
                
                /* set the partial design matrix */
                gsl_spmatrix_set(M_temp, k, (peakUpperLimitIndex - peakLowerLimitIndex) * i, area * idealSignalValue);
            }
            
            /* add the partial matrix to the final one */
            //M_temp = gsl_spmatrix_ccs(M_temp);  //cant use the compression, because we need to change the elements later
//            gsl_spmatrix_add(M, M, M_temp);
            
            for(int k = 0; k < dataLength; k++)
            {
                for(int l = 0; l < moleculeCount; l++)
                {
                    gsl_spmatrix_set(M, k, l, gsl_spmatrix_get(M, k, l) + gsl_spmatrix_get(M_temp, k, l));
                }
            }
            
            gsl_spmatrix_free(M_temp);
        }
    }
    
    /* Apply fitmask to design matrix and signal */
    for (int i = 0; i < dataLength; i++)
    {
        if(!Fitmask[i])
        {
            for(int j = 0; j < moleculeCount; j++)
            {
                gsl_spmatrix_set(M, i, j, 0);
            }
            
            Signal[i] = 0;
        }
    }
    
    /* Solve the system */
    gsl_multilarge_linear_workspace *Wrk;
    Wrk = gsl_multilarge_linear_alloc(gsl_multilarge_linear_tsqr, moleculeCount);
    
    gsl_matrix *Mdense = gsl_matrix_alloc(dataLength, moleculeCount);
    gsl_spmatrix_sp2d(Mdense, M);
    
    gsl_vector *Signalgsl = gsl_vector_alloc(dataLength);
    for (int i = 0; i < dataLength; i++)
    {
        gsl_vector_set(Signalgsl, i, Signal[i]);
    }
    
    gsl_multilarge_linear_accumulate(Mdense, Signalgsl, Wrk);
    
    //TODO: unfinished, because the previous stuff is too slow
}

void test2() {
    std::cout << "fittingtest2 test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (fittingtest2) message=error message sample" << std::endl;
        
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% fittingtest2" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (fittingtest2)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (fittingtest2)" << std::endl;

//    std::cout << "%TEST_STARTED% test2 (fittingtest2)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (fittingtest2)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

