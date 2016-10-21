/**
 * IsotopeFitter
 * DebugUtils.cpp
 *  
 * @author Michal Durian
 * @version 21.10.2016 15:41 MD
 * 
 * Changes log:
 * 
 */

/* Headers */
#include "../include/DebugUtils.h"

/* Namespaces */
using namespace std;

/* Fields */
chrono::time_point<chrono::system_clock> timeStart, timeEnd, timeStartLoop, timeEndLoop;
chrono::duration<double> elapsed, elapsedLoop;

void WriteMatrixToFile(gsl_matrix *Matrix, char *fileName)
{
    char* format[1] = {"%f"};
    FILE *file = fopen(fileName, "w");
    gsl_matrix_fprintf(file, Matrix, *format);
    fclose(file);
}

/* Overload for sparse matrix */
void WriteMatrixToFile(gsl_spmatrix *Matrix, char *fileName)
{
    char* format[1] = {"%f"};
    FILE *file = fopen(fileName, "w");
    gsl_spmatrix_fprintf(file, Matrix, *format);
    fclose(file);
}