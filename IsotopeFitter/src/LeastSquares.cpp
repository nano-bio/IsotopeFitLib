/**
 * IsotopeFitter
 * LeastSquares.cpp
 * 
 * @author Michal Durian
 * @version 21.10.2016 15:54 MD
 */

#include "../include/LeastSquares.h"

using namespace std;

/**
 * Calculates the optimal regularization parameter for system currently loaded in GSL workspace
 * by calculating the L-curve and searching for point of highest curvature.
 * 
 * @param *WrkSpc - Pointer to GSL workspace where the least squares system has been previously loaded.
 * @return - Value of the optimal regularization parameter.
 */
double GetOptimalRegParam(gsl_multilarge_linear_workspace *WrkSpc)
{
    int fnResult;
    
    /* Needed for L-curve calculation */
    size_t lCurveLength = 1000;
    gsl_vector *RegParams_v = gsl_vector_alloc(lCurveLength);
    gsl_vector *ResNorms_v = gsl_vector_alloc(lCurveLength);
    gsl_vector *SolNorms_v = gsl_vector_alloc(lCurveLength);
    
    /* Calculate the L curve */
    fnResult = gsl_multilarge_linear_lcurve(RegParams_v, ResNorms_v, SolNorms_v, WrkSpc);
        
    if(fnResult != 0)
    {
        //TODO: error
    }
    
    /* Remove duplicate values from results of L curve, because otherwise the function looking for optimal regularization parameter will fail.
     * We first sort all three vectors together then find all unique values and erase the rest. */
    vector<tuple<int,double,double> > LCurveParams(lCurveLength);
    
    for(int i=0; i < lCurveLength; i++)
    { 
        get<0>(LCurveParams[i]) = gsl_vector_get(ResNorms_v, i);
        get<1>(LCurveParams[i]) = gsl_vector_get(SolNorms_v, i);
        get<2>(LCurveParams[i]) = gsl_vector_get(RegParams_v, i);
    }
    
    gsl_vector_free(ResNorms_v);
    gsl_vector_free(SolNorms_v);
    gsl_vector_free(RegParams_v);
    
    sort(LCurveParams.begin(), LCurveParams.end(), [&](tuple<int,double,double> A, tuple<int,double,double> B) -> bool { return get<0>(A) < get<0>(B); });
       
    /* Find and remove all unique entries in ResNorms_v vector, which serves as x-axis if the L curve */
    auto UniqueIterator = unique(LCurveParams.begin(), LCurveParams.end(), [&](tuple<int,double,double> A, tuple<int,double,double> B) { return get<0>(A) == get<0>(B); });
    LCurveParams.erase(UniqueIterator, LCurveParams.end());
    
    /* we have to copy the data back into gsl containters */
    gsl_vector *ResNorms2_v = gsl_vector_alloc(LCurveParams.size());
    gsl_vector *SolNorms2_v = gsl_vector_alloc(LCurveParams.size());
    gsl_vector *RegParams2_v = gsl_vector_alloc(LCurveParams.size());
    
    for(int i=0; i < LCurveParams.size(); i++)
    {
        gsl_vector_set(ResNorms2_v, i, get<0>(LCurveParams[i]));
        gsl_vector_set(SolNorms2_v, i, get<1>(LCurveParams[i]));
        gsl_vector_set(RegParams2_v, i, get<2>(LCurveParams[i]));
    }
    
    /* Find the index of optimal regularization parameter */
    size_t regParIndex;
    
    fnResult = gsl_multifit_linear_lcorner(ResNorms2_v, SolNorms2_v, &regParIndex);
    
    if(fnResult != 0)
    {
        //TODO: error
    }
    
    double retval = gsl_vector_get(RegParams2_v, regParIndex);
    
    gsl_vector_free(ResNorms2_v);
    gsl_vector_free(SolNorms2_v);
    gsl_vector_free(RegParams2_v);
    
    return retval;
}