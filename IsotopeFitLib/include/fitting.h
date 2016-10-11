#ifndef FITTING_H
#define FITTING_H

/* Headers */
#include <gsl/gsl_fit.h>
#include <gsl/gsl_spline.h>

#include <iostream>
#include <vector>

/* Namespaces */
using namespace std;

/* Exported functions */
void FitResolution(const vector<double> &COMList, const vector<double> &ResolutionList, const int &method, double &outC0, double &outC1);
void FitMassOffsets(const vector<double> &COMList, const vector<double> &MassOffsetList, const int &method, const vector<double> &MassAxis, vector<double> &MassAxisCorr);
void FitBaseline(const vector<double> &BgMass, const vector<double> &BgY, const vector<double> &MassAxis, vector<double> &OutBaseline);

#endif /* FITTING_H */