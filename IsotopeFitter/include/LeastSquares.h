/**
 * IsotopeFitter
 * LeastSquares.h
 * 
 * Purpose: Contains functions to solve least squares system.
 * 
 * @author Michal Durian
 * @version 21.10.2016 15:54 MD
 */

#ifndef LEASTSQUARES_H
#define LEASTSQUARES_H

/* Standard headers */
#include <vector>
#include <tuple>
#include <algorithm>

#include <gsl/gsl_multilarge.h>
#include <gsl/gsl_multifit.h>

double GetOptimalRegParam(gsl_multilarge_linear_workspace *WrkSpc);

#endif /* LEASTSQUARES_H */

