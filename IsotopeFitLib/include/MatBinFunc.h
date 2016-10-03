#ifndef MATBINFUNC_H
#define MATBINFUNC_H

/* System headers */
//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

/* External headers */

/* Namespaces */
using namespace std;

fstream OpenMatBinFile(string fileName);
void ReadMatBinFile(fstream &File, char* outBuffer);
void CloseMatBinFile(fstream &File);


#endif /* MATBINFUNC_H */

