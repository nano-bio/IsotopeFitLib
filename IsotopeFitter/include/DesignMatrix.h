/**
 * IsotopeFitter
 * DesignMatrix.h
 * 
 * Purpose:
 * Contains functions that are needed in the design matrix build loop. They are listed in chronological order, as they are called.
 * 
 * @author Michal Durian
 * @version 21.10.2016 15:38 MD
 * 
 * Changes log:
 * 
 */

#ifndef DESIGNMATRIX_H
#define DESIGNMATRIX_H

/* Standard headers */
#include <vector>
#include <algorithm>

/* GSL headers */
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

/* Project headers */
#include "../../IsotopeFitLib/include/ifl_data.h"

/* Namespaces */
using namespace std;

/* Exported functions */
void TransformShapeBreaks(const Calibration_t &CalibData, const double &fwhm, const double &mass, vector<double> &OutBreaksRecalc);
void TransformShapeCoefs(const Calibration_t &CalibData, const double &fwhm, const double &area, gsl_matrix *OutShapeCoefsRecalc_m);
int FindLowerLimitIndex(const vector<double> &SearchVect, double threshold);
int FindUpperLimitIndex(const vector<double> &SearchVect, double threshold);

#endif /* DESIGNMATRIX_H */

