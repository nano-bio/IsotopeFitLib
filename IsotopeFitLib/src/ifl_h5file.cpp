/**
 * IsotopeFitLib
 * ifl_ifdfile.cpp
 * 
 * @author Michal Durian
 * @version 21.10.2016 16:15 MD
 * 
 * Changes log:
 * 
 */

#include "../include/ifl_h5file.h"

/* Function implementations */
/* Checks, if the file specified is a H5 file */
bool IsH5File(string fileName)
{    
    return H5File::isHdf5(fileName);    
}

/* Opens specified H5 file, returns handle */
H5File OpenH5File(string fileName)
{
    H5File file(fileName, H5F_ACC_RDWR);
    return file;
}

/* Closes specified H5 file */
void CloseH5File(H5File file)
{
    file.close();
}

/* Opens specified attribute from specified file and returns handle */
Attribute OpenH5Attribute(H5File file, string attributeName)
{
    Attribute att = file.openAttribute(attributeName);
    return att;
}

/* Reads value of specified attribute and writes it to specified buffer */
int ReadH5AttributeInt(Attribute att)
{
    int out;
    att.read(att.getDataType(), &out);
    return out;
}

float ReadH5AttributeFloat(Attribute att)
{
    float out;
    att.read(att.getDataType(), &out);
    return out;
}

string ReadH5AttributeString(Attribute att)
{
    string out;
    att.read(att.getDataType(), &out);
    return out;
}

/* Closes specified H5 Attribute */
void CloseH5Attribute(Attribute att)
{
    att.close();
}

/* Opens specified dataset from specified file and returns handle */
DataSet OpenH5DataSet(H5File file, string dataSetName)
{
    DataSet ds = file.openDataSet(dataSetName);
    return ds;
}

/* Reads data from specified dataset and writes them to specified buffer */
void ReadH5DataSet(DataSet dataSet, float buffer[])
{    
    dataSet.read(buffer, dataSet.getDataType());
}

/* Closes specified H5 dataset */
void CloseH5DataSet(DataSet ds)
{
    ds.close();
}