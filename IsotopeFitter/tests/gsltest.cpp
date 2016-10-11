#include <stdlib.h>
#include <iostream>

#include "src/IsotopeFitter.h"
#include <stdio.h>

/* pre test 1, F */
#include <gsl/gsl_fit.h>
#include <gsl/gsl_poly.h>

/* pre test F */
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_math.h>

/* pre test 2 */
#include <gsl/gsl_spline.h>
#include <math.h>

void test1() {
    std::cout << "gsltest test 1" << std::endl;
    
    int i, n = 4;
    double x[4] = { 1970, 1980, 1990, 2000 };
    double y[4] = { 12, 11, 14, 13 };
    double w[4] = { 0.1, 0.2, 0.3, 0.4 };
    
    double c0, c1, cov00, cov01, cov11, chisq;

    gsl_fit_wlinear (x, 1, w, 1, y, 1, n, &c0, &c1, &cov00, &cov01, &cov11, &chisq);
    
    printf ("# best fit: Y = %g + %g X\n", c0, c1);
    printf ("# covariance matrix:\n");
    printf ("# [ %g, %g\n#%g, %g]\n", cov00, cov01, cov01, cov11);
    printf ("# chisq = %g\n", chisq);

    for (i = 0; i < n; i++)
        //printf ("data: %g %g %g\n", x[i], y[i], 1/sqrt(w[i]));
        printf ("\n");

    for (i = -30; i < 130; i++)
    {
        double xf = x[0] + (i/100.0) * (x[n-1] - x[0]);
        double yf, yf_err;
        
        gsl_fit_linear_est (xf, c0, c1, cov00, cov01, cov11, &yf, &yf_err);
        
        printf ("fit: %g %g\n", xf, yf);
        printf ("hi :%g %g\n", xf, yf + yf_err);
        printf ("lo :%g %g\n", xf, yf - yf_err);
    }
    
}

void test2() {
    std::cout << "gsltest test 2" << std::endl;
    
    int i;
    double xi, yi, x[10], y[10];
    
    printf ("#m=0,S=2\n");

    for (i = 0; i < 10; i++)
    {
        x[i] = i + 0.5 * sin (i);
        y[i] = i + cos (i * i);
        printf ("%g %g\n", x[i], y[i]);
    }
    
    printf ("#m=1,S=0\n");
    {
        gsl_interp_accel *acc = gsl_interp_accel_alloc ();
        gsl_spline *spline = gsl_spline_alloc (gsl_interp_cspline, 10);
        gsl_spline_init (spline, x, y, 10);
    
        for (xi = x[0]; xi < x[9]; xi += 0.01)
        {
            yi = gsl_spline_eval (spline, xi, acc);
            printf ("%g %g\n", xi, yi);
        }
        gsl_spline_free (spline);
        gsl_interp_accel_free (acc);
    }
    
}

void test3() {
    std::cout << "gsltest test 3" << std::endl;
    
    /* Load data */
    string str = "/home/matlab/Michal/dev/IsotopeFitter/tests/testfileifd2.ifd";
    LoadIFDFile(str);
    
    double *massaxis = &IFData::RawData[0][0];    
    size_t masaxsize = IFData::RawData[0].size();
    
    cout << massaxis[0] << " " << massaxis[masaxsize-1] << endl;
    
    double *bgm = &IFData::BGCorrectionData.Bgm[0];
    double *bgy = &IFData::BGCorrectionData.Bgy[0];
    size_t size = IFData::BGCorrectionData.Bgm.size();
    
    cout << endl;
    for (int j=0; j<size; j++)
    {
        cout << IFData::BGCorrectionData.Bgm[j] << " " << IFData::BGCorrectionData.Bgy[j] << endl;
    }
    cout << endl;
    
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *spline = gsl_spline_alloc (gsl_interp_steffen, size);   //gsl_interp_cspline
    int result = gsl_spline_init (spline, bgm, bgy, size);
    cout << "bgcorr res " << result << endl;
    
    cout << endl;
    double xi, yi;
    
    for (xi = massaxis[0]; xi < massaxis[masaxsize-1]; xi += 10)
    {
        //yi = gsl_spline_eval (spline, xi, acc);
        spline->interp->type->eval(spline->interp->state, &bgm[0], &bgy[0], spline->interp->size, xi, acc, &yi);
        printf ("%g %g\n", xi, yi);
    }
    cout << endl;
    
    //TODO: subtract the evaluated curve from rawdata
}

void testF() {
    std::cout << "gsltest test F" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (gsltest) message=error message sample" << std::endl;
    
    /* Load data */
    string str = "/home/matlab/Michal/dev/IsotopeFitter/tests/testfileifd2.ifd";
    LoadIFDFile(str);
    
    /* Load raw data */
    double *massaxis = &IFData::RawData[0][0];
    double *signal = &IFData::RawData[1][0];
    size_t rawsize = IFData::RawData[0].size();
    
    /* Mass offset fit */
    //alloc gsl_interp_alloc
    //init gsl_interp_init
    //gsl_interp_free
    //type gsl_interp_cspline
    //gsl_interp_name
    //gsl_interp_min_size
    //gsl_interp_eval - there is more of them
    //spline instead of interp
    
    double *x_comlist = &IFData::CalibrationData.COMList[0];
    double *y_massofset = &IFData::CalibrationData.MassOffsetList[0];
    size_t size = IFData::CalibrationData.COMList.size();
    
    cout << endl;
    for (int j = 0; j < size; j++)
    {
        cout << IFData::CalibrationData.COMList[j] << " " << IFData::CalibrationData.MassOffsetList[j] << endl;
    }
    cout << endl;
    
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *spline = gsl_spline_alloc (gsl_interp_steffen, size);   //gsl_interp_cspline
    int result = gsl_spline_init (spline, x_comlist, y_massofset, size);
    cout << "mass ofset res " << result << endl;
    
    cout << endl;
    double xi, yi;
    
    /* create corrected mass axis */
    double massaxisCorr[rawsize] = {};
    
    for (xi = x_comlist[0]; xi < x_comlist[size-1]; xi += 1)
    {
        
        //spline->interp->type->eval(spline->interp->state, &x_comlist[0], &y_massofset[0], spline->interp->size, xi, acc, &yi);
        
//        yi = gsl_spline_eval (spline, xi, acc);
//        printf ("%g %g\n", xi, yi);
    }
    cout << endl;
      
//    for (int i=0; i<rawsize; i++)
//    {
//        massaxisCorr[i] = massaxis[i] - 
//    }
    
    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
    
    /* Resolution fit */
    double *x = &IFData::CalibrationData.COMList[0];
    double *y = &IFData::CalibrationData.ResolutionList[0];
    int n = IFData::CalibrationData.COMList.size();
    
    double c[2] = {};
    double cov00, cov01, cov11, sumsq;
    
    int res = gsl_fit_linear(x, 1, y, 1, n, &c[0], &c[1], &cov00, &cov01, &cov11, &sumsq);
    
    for (int j=0; j<n; j++)
    {
        cout << IFData::CalibrationData.COMList[j] << " " << IFData::CalibrationData.ResolutionList[j] << endl;
    }
    
    cout << "resolution res " << res << endl;
    
//    printf ("# best fit: Y = %g + %g X\n", c[0], c[1]);
//    printf ("# covariance matrix:\n");
//    printf ("# [ %g, %g\n#%g, %g]\n", cov00, cov01, cov01, cov11);
//    printf ("# sumsq = %g\n", sumsq);
    
    int n_mol = IFData::MoleculesData.size();
    
    /* From molecule peakdata */
    double mass, area, R, fwhm, coefs_temp;
    double *breaksRecalc;
    
    /* Load some more data */
    double *breaks = &IFData::CalibrationData.Shape.Breaks[0];
    
    /* Load coefs into matrix */
    gsl_matrix *coefs = gsl_matrix_alloc(IFData::CalibrationData.Shape.Coefs.size(), IFData::CalibrationData.Shape.Coefs[0].size());
    
    for (int j=0; j<IFData::CalibrationData.Shape.Coefs.size(); j++)
    {
        for (int k=0; k<IFData::CalibrationData.Shape.Coefs[j].size(); k++)
        {
            gsl_matrix_set(coefs, j, k, IFData::CalibrationData.Shape.Coefs[j][k]);
        }
    }
    
    /* Loop through molecules */
    for(int i=0; i<n_mol; i++)
    {
        /* Loop through isotope peaks */
        for(int j=0; j<n_mol; j++)
        {
            /* Load values from data*/
            mass = IFData::MoleculesData[i].PeakData[j][0];
            area = IFData::MoleculesData[i].PeakData[j][1];
            
            /* Calculate resolution and fwhm */
            R = gsl_poly_eval(c, 2, mass);
            fwhm = mass/R;
            
            if(fwhm < 0)
            {
                throw "fhwm negative";
            }
            
            /* Peakshape recalculation */
            for(int k=0; k<IFData::CalibrationData.Shape.Breaks.size(); k++)
            {
                breaksRecalc[k] = breaks[k] * fwhm;
            }
            
            for (int l=0; l<IFData::CalibrationData.Shape.Coefs.size(); l++)
            {
                for (int k=0; k<IFData::CalibrationData.Shape.Coefs[l].size(); k++)
                {
                    switch(k%4)
                    {
                        case 0 :
                        {
                            coefs_temp = gsl_matrix_get(coefs, l, k) / gsl_pow_3(fwhm);
                            break;
                        }
                        case 1 :
                        {
                            coefs_temp = gsl_matrix_get(coefs, l, k) / gsl_pow_2(fwhm);
                            break;
                        }
                        case 2 :
                        {
                            coefs_temp = gsl_matrix_get(coefs, l, k) / fwhm;
                            break;
                        }
                        case 3 :
                        {
                            coefs_temp = gsl_matrix_get(coefs, l, k);
                            break;
                        }
                    }
                    
                    /* Area normalization */
                    coefs_temp = coefs_temp * area / fwhm;
                    gsl_matrix_set(coefs, l, k, coefs_temp);
                }
            }
            
            /* find massrange  */
            
        }
    }
    
//    cout << "Breaks " << endl;
//    for (int j=0; j<10; j++)
//    {
//        cout << IFData::CalibrationData.Shape.Breaks[j] << endl;
//    }    
//    cout << "Coefs " << endl;
//    for (int j=0; j<IFData::CalibrationData.Shape.Coefs.size(); j++)
//    {
//        for (int k=0; k<IFData::CalibrationData.Shape.Coefs[j].size(); k++)
//        {
//            cout << IFData::CalibrationData.Shape.Coefs[j][k] << "\t";
//        }
//        cout << endl;
//    } 
    
//    for(int k = 0; k < IFData::MoleculesData[i].PeakData.size(); k++)
//        {
//            for(int l = 0; l < IFData::MoleculesData[i].PeakData[k].size(); l++)
//            {
//                cout << IFData::MoleculesData[i].PeakData[k][l] << " ";
//            }
//            cout << endl;
//        }
    
    //double gsl_poly_eval(const double c[], const int len, const double x)
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% gsltest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

//    std::cout << "%TEST_STARTED% test1 (gsltest)" << std::endl;
//    test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (gsltest)" << std::endl;

//    std::cout << "%TEST_STARTED% test2 (gsltest)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (gsltest)" << std::endl;
    
    std::cout << "%TEST_STARTED% test3 (gsltest)\n" << std::endl;
    test3();
    std::cout << "%TEST_FINISHED% time=0 test3 (gsltest)" << std::endl;
    
//    std::cout << "%TEST_STARTED% testF (gsltest)\n" << std::endl;
//    testF();
//    std::cout << "%TEST_FINISHED% time=0 testF (gsltest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

