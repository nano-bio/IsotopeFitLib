/**
 * IsotopeFitLib
 * ifl_ifdfile.h
 * 
 * Purpose:
 * Contains functions for working with HDF5 files. Is meant to be a wrapper over the HDF5 API.
 * 
 * @author Michal Durian
 * @version 21.10.2016 16:15 MD
 * 
 * Changes log:
 * 
 */

#ifndef HDF5FUNC_H
#define HDF5FUNC_H

/* System headers */
//#include <cstdlib>
#include <iostream>

/* External headers */
#include <H5Cpp.h>
//#include <H5File.h>

/* Namespaces */
using namespace std;
using namespace H5;

/* Exported function declarations */
/* H5 file functions */
bool IsH5File(string fileName);
H5File OpenH5File(string fileName);
void CloseH5File(H5File file);

/* H5 attribute functions */
Attribute OpenH5Attribute(H5File file, string attributeName);
int ReadH5AttributeInt(Attribute att);
float ReadH5AttributeFloat(Attribute att);
string ReadH5AttributeString(Attribute att);
void CloseH5Attribute(Attribute att);

/* H5 dataset functions */
DataSet OpenH5DataSet(H5File file, string dataSetName);
void ReadH5DataSet(DataSet dataSet, float buffer[]);
void CloseH5DataSet(DataSet dataSet);

#endif /* HDF5FUNC_H */

