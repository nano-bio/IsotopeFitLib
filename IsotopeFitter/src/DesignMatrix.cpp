/**
 * IsotopeFitter
 * DesignMatrix.cpp
 * 
 * @author Michal Durian
 * @version 21.10.2016 15:38 MD
 * 
 * Changes log:
 * 
 */

#include "../include/DesignMatrix.h"

using namespace std;

/**
 * Transforms the peak shape partial polynomial breaks according to mass and FWHM.
 * 
 * @param &CalibData - Reference to the struct containing calibration data, loaded previously from IFD file.
 * @param &fwhm - Reference to FWHM value.
 * @param &mass - Reference to the value of mass of current isotope.
 * @param &OutBreaksRecalc - Reference to the vector, where the recalculated breaks will be written.
 */
void TransformShapeBreaks(const Calibration_t &CalibData, const double &fwhm, const double &mass, vector<double> &OutBreaksRecalc)  //TODO: add the struct reference passing everywhere
{
    for(int i = 0; i < CalibData.Shape.Breaks.size(); i++)
    {
        OutBreaksRecalc[i] = CalibData.Shape.Breaks[i] * fwhm + mass;
    }
}

/**
 * Transforms the coefficients of peak shape partial polynomials according to FWHM and area under the peak.
 * 
 * @param &CalibData - Reference to the struct containing calibration data, loaded previously from IFD file.
 * @param &fwhm - Reference to FWHM value.
 * @param &area - Reference to the area value of the peak of current isotope.
 * @param *OutShapeCoefsRecalc_m - Pointer to the GSL matrix, where the recalculated coefficients will be written.
 */
void TransformShapeCoefs(const Calibration_t &CalibData, const double &fwhm, const double &area, gsl_matrix *OutShapeCoefsRecalc_m)
{
    for (int i = 0; i < CalibData.Shape.Coefs.size(); i++)
    {
        for (int j=0; j < CalibData.Shape.Coefs[i].size(); j++)
        {           
            /* 4 is hardcoded, since it expects four coefficients of a cubic spline for each row of the coefficient matrix. */
            switch(j % 4)
            {
                case 0 :
                {
                    gsl_matrix_set(OutShapeCoefsRecalc_m, i, j, CalibData.Shape.Coefs[i][j] * area / gsl_pow_4(fwhm));
                    break;
                }
                case 1 :
                {
                    gsl_matrix_set(OutShapeCoefsRecalc_m, i, j, CalibData.Shape.Coefs[i][j] * area / gsl_pow_3(fwhm));
                    break;
                }
                case 2 :
                {
                    gsl_matrix_set(OutShapeCoefsRecalc_m, i, j, CalibData.Shape.Coefs[i][j] * area / gsl_pow_2(fwhm));
                    break;
                }
                case 3 :
                {
                    gsl_matrix_set(OutShapeCoefsRecalc_m, i, j, CalibData.Shape.Coefs[i][j] * area / fwhm);
                    break;
                }
            }
        }                
    }
}

/**
 * Finds the index of first element, value of which is bigger than the threshold.
 * 
 * @param &SearchVect - Reference to the vector, which is being searched in.
 * @param threshold - Value that we are using as comparison criterion.
 * @return Index of the element.
 */
int FindLowerLimitIndex(const vector<double> &SearchVect, double threshold)
{    
    auto searchIterator = lower_bound(SearchVect.begin(), SearchVect.end(), threshold);
    return distance(SearchVect.begin(), searchIterator);
}

/**
 * Finds the index of last element, value of which is not bigger than the threshold.
 * 
 * @param &SearchVect - Reference to the vector, which is being searched in.
 * @param threshold - Value that we are using as comparison criterion.
 * @return Index of the element.
 */
int FindUpperLimitIndex(const vector<double> &SearchVect, double threshold)
{
    auto searchIterator = upper_bound(SearchVect.begin(), SearchVect.end(), threshold);
    return distance(SearchVect.begin(), searchIterator) - 1;    // -1 because we want the inner bound of the interval
}