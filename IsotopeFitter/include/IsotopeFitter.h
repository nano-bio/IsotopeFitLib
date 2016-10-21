/**
 * IsotopeFitter
 * IsotopeFitter.h
 * 
 * Purpose:
 * Main header file of fitting program. Takes care of all necessary includes.
 * 
 * @author Michal Durian
 * @version 21.10.2016 15:33 MD
 * 
 * Changes log:
 * 
 */

#ifndef ISOTOPEFITTER_H
#define ISOTOPEFITTER_H

//TODO: they might not all be necessary after cleanup
/* Standard headers*/
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdio>
#include <fstream>
#include <iomanip>

/* GSL Headers */
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_multilarge.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_multilarge.h>

/* Project headers */
#include "../../IsotopeFitLib/include/ifl.h"
#include "../include/DesignMatrix.h"
#include "../include/LeastSquares.h"
#ifdef DEBUG
#include "../include/DebugUtils.h"
#endif

/* Namespaces */
using namespace std;

#endif /* ISOTOPEFITTER_H */

