/**
 * IsotopeFitLib
 * ifl_dataprocessing.h
 * 
 * Purpose:
 * Contains functions that perform corrections of raw data according to supplied calibration data.
 * 
 * @author Michal Durian
 * @version 17.10.2016 12:52 MD
 * 
 * Changes log:
 * 
 */

#ifndef IFL_DATAPROCESSING_H
#define IFL_DATAPROCESSING_H

/* Stndard headers */
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
//#include <iterator>
//#include <iomanip>

/* GSL headers */
//#include <gsl/gsl_fit.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_spline.h>

/* Project headers */
#include "ifl_data.h"

/* Namespaces */
using namespace std;

/* Exported functions */
void CorrectBaseline(const BGCorrection_t BGCorrData, const vector<vector<double> > &RawData, vector<double> &OutCorrSignal);
void CorrectMassOffsets(const Calibration_t CalData, const vector<double> &RawMassAxis, vector<double> &OutMassAxisCorr);
void FitResolution(const Calibration_t CalData, vector<double> &OutFitCoefs);

#endif /* IFL_DATAPROCESSING_H */

