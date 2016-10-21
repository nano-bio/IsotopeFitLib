/**
 * IsotopeFitter
 * DebugUtils.h
 * 
 * Purpose: 
 * Contains small helpful functions for profiling, debugging and testing the program.
 * It compiles into the code only in debug configuration.
 * 
 * @author Michal Durian
 * @version 21.10.2016 15:41 MD
 * 
 * Changes log:
 * 
 */

#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

/* Standard headers */
#include <iostream>
#include <chrono>
#include <vector>
#include <iostream>
#include <typeinfo>

/* GSL headers */
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_spmatrix.h>

/* Namespaces */
using namespace std;

/* Exported fields */
extern chrono::time_point<chrono::system_clock> timeStart, timeEnd, timeStartLoop, timeEndLoop;
extern chrono::duration<double> elapsed, elapsedLoop;

/* Functions to write GSL matrices to a file. */
void WriteMatrixToFile(gsl_matrix *Matrix, char *fileName);
void WriteMatrixToFile(gsl_spmatrix *Matrix, char *fileName);

/* Function to write vector, gsl vector or vector of tuples to a text file. It is a template function, that is why it has to be defined in header file. */
template<typename T> void WriteVectorToFile(vector<T> V, char *fileName)
{
    //TODO: write it, double, int, tuple
    
    if(typeid(T) == typeid(double))
    {
        cout << "je to double" << endl;
    }
    
//    ofstream mtxSort;
//    mtxSort.open("mtxsort");
//    
//    for (int i = 0; i < DesignSort.size(); i++)
//    {
//        mtxSort << get<0>(DesignSort[i]) << " " << get<1>(DesignSort[i]) << " " << get<2>(DesignSort[i]) << endl;
//    }
//    mtxSort.close();
    
    
    //    gsl_matrix *DesignTEST_mDens = gsl_matrix_alloc(Design_m->size1, Design_m->size2);
//    gsl_spmatrix_sp2d(DesignTEST_mDens, Design_m);
    //    ofstream origsignal;
//        origsignal.open("origsignal");
//    for(int i=0; i < dataLength; i++)
//    {
//        origsignal << Signal[i] << endl;
//    }
//        origsignal.close();
    
    //    ofstream origDesmatrix;
//        origDesmatrix.open("origDesmatrix");
//
//        for (int i = 0; i < DesignTEST_mDens->size1; i++)
//        {
//            for (int j = 0; j < DesignTEST_mDens->size2; j++)
//            {
//                origDesmatrix << gsl_matrix_get(DesignTEST_mDens, i ,j) << " ";
//            }
//            origDesmatrix << endl;
//        }
//    origDesmatrix.close();
        
    //    ofstream fitmasked;
//    fitmasked.open("fitmasked");
//    for(int i=0; i<MassSigMaskTuple.size(); i++)
//    {
//        fitmasked << get<0>(MassSigMaskTuple[i]) << " " << get<1>(MassSigMaskTuple[i]) << endl;
//    }
//    fitmasked.close();
    
        
//    for (int i = 0; i < MassSigMaskTuple.size(); i++)
//    {
//        calcSpec << get<0>(MassSigMaskTuple[i]) << " " << gsl_vector_get(CalcSignal, i) << " " << get<1>(MassSigMaskTuple[i]) << endl;
//    }
    

}

/* Functions to determine time elapsed by block of code. */
inline void tic()
{
    timeStart = chrono::system_clock::now();
}

inline void toc(string description)
{
    timeEnd = chrono::system_clock::now();
    elapsed = timeEnd - timeStart;
    cout << description << " " << elapsed.count() << "s" << endl;
}

inline void ticloop()
{
    timeStartLoop = chrono::system_clock::now();
}

inline void tocloop(string description)
{
    timeEndLoop = chrono::system_clock::now();
    elapsedLoop = timeEndLoop - timeStartLoop;
    cout << description << " " << elapsedLoop.count() << "s" << endl;
}

#endif /* DEBUGUTILS_H */