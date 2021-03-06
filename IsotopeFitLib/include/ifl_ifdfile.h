/**
 * IsotopeFitLib
 * ifl_ifdfile.h
 * 
 * Purpose:
 * Contains functions for reading and writing (TODO) IFD files.
 * 
 * @author Michal Durian
 * @version 21.10.2016 16:15 MD
 * 
 * Changes log:
 * 
 */

#ifndef IFL_IFDFILE_H
#define IFL_IFDFILE_H

/* Standard headers */
#include <string>
#include <vector>
#include <zlib.h>
#include <matio.h>
#include <iostream>
#include <exception>
#include <fstream>

/* Project headers */
#include "ifl_data.h"

/* Namespaces */
using namespace std;

/* Struct declarations */
/* Struct for single molecule data */
//typedef struct Molecule_t
//{
//    vector<vector<double> > PeakData;
//    string name;
//    double minMass;
//    double maxMass;
//    double com;
//    double minInd;
//    double maxInd;
//    double area;
//    double areaError;
//    double rootIndex;
//}Molecule_t;

/* Struct for calibration shape data */
//typedef struct Shape_t
//{
//    string form;
//    vector<double> Breaks;
//    vector<vector<double> > Coefs;
//    double pieces;
//    double order;
//    double dim;
//}Shape_t;

/* Struct for calibration data */
//typedef struct Calibration_t
//{
//    vector<double> COMList;
//    vector<double> MassOffsetList;
//    vector<double> ResolutionList;
//    string MassOffsetMethod;
//    string ResolutionMethod;
//    double massOffsetParam;
//    double resolutionParam;
//    vector<string> NameList;
//    Shape_t Shape;
//}Calibration_t;

/* Struct for background correction data*/
//typedef struct BGCorrection_t
//{
//    double startMass;
//    double endMass;
//    double nDiv;
//    double percent;
//    vector<double> Bgm;
//    vector<double> Bgy;
//}BGCorrection_t;

/* Struct for file information */
//typedef struct FileInfo_t
//{
//    string originalFileName;
//    string fileName;
//    string pathName;
//    string h5CompletePath;
//}FileInfo_t;

/* Struct to pack all data together. Maybe we will use it later */
//struct IFData_t
//{
//    vector<vector<double> > RawData;
//    double startInd;
//    double endInd;
//    vector<Molecule_t> MoleculesData;
//    Calibration_t CalibrationData;
//    BGCorrection_t BGCorrectionData;
//    vector<double> GUIStatus;
//    FileInfo_t FileInfoData;
//}IFData_t;

/* Exported data objects */
//namespace IFData
//{
//    extern vector<vector<double> > RawData;
//    extern double startInd;
//    extern double endInd;
//    extern vector<Molecule_t> MoleculesData;
//    extern Calibration_t CalibrationData;
//    extern BGCorrection_t BGCorrectionData;
//    extern vector<double> GUIStatus;
//    extern FileInfo_t FileInfoData;
//}

/* Exported functions for IFD files */
void LoadIFDFile(string fileName);



#endif /* IFL_IFDFILE_H */