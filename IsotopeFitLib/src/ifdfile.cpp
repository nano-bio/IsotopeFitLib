//TODO: split LoadIFDFile into methods
//TODO: rewrite data storage in gsl standard?

/* Headers */
#include "../include/ifdfile.h"
#include <iostream>
#include <exception>
#include <fstream>

/* Namespaces */
using namespace std;
using namespace IFData;

/* Declaration of data objects */
vector<vector<double> > IFData::RawData;
double IFData::startInd;
double IFData::endInd;
vector<Molecule_t> IFData::MoleculesData;
Calibration_t IFData::CalibrationData;
BGCorrection_t IFData::BGCorrectionData;
vector<double> IFData::GUIStatus;
FileInfo_t IFData::FileInfoData;

/* Enum declarations */
enum DataFields
{
    RAWDATA,
    STARTIND,
    ENDIND,
    MOLECULES,
    CALIBRATION,
    BGCORRECTIONDATA,
    GUISTATUSVECTOR,
    FILEINFO
};

/* Exceptions */
class InvalidFilePathException : public exception
{
public:
    InvalidFilePathException() {}
    
    virtual const char* what() const throw()
    {
        return "Specified path is not valid.";
    }
};

class NotIFDFileException : public exception
{
public:
    NotIFDFileException() {}
    
    virtual const char* what() const throw()
    {
        return "Specified file is not an IFD file.";
    }
};

class InvalidIFDFileException : public exception
{
public:
    InvalidIFDFileException() {}    
    
    virtual const char* what() const throw()
    {
        return "Specified file is not a valid IFD file.";
    }
};

/* Exported functions */

/* Loads data from IFD file into vectors. It is specifically tailored, if file format changes, we are doomed. */
void LoadIFDFile(string fileName)
{
    /* Checks if the path is a valid one */
    ifstream testPath(fileName);
    if(!testPath)
    {
        throw InvalidFilePathException();
    }           
    
    /* Checks if the file path points to something else than IFD file */
    if(fileName.find(".ifd") == string::npos)
    {
        throw NotIFDFileException();
    }
    
    /* Loads the file with read-only privileges*/
    mat_t *file = Mat_Open(fileName.c_str(), MAT_ACC_RDONLY);
    
    if(NULL == file)
    {
        throw InvalidIFDFileException();
    }
    
    /* Reads data for the root level structure, name of which is hardcoded "data" */
    matvar_t *topLevelStruct = Mat_VarRead(file, "data");
    //cout << "pointer " << topLevelStruct << endl;

       
    /* Loading all data fields of the root structure into a vector TopLevelStructFields for later access */
    vector<matvar_t> TopLevelStructFields;
    
    TopLevelStructFields.resize(Mat_VarGetNumberOfFields(topLevelStruct));
    //cout << "check " << Mat_VarGetNumberOfFields(topLevelStruct) << " " << topLevelStruct << endl;
    
    for(int i = 0; i < Mat_VarGetNumberOfFields(topLevelStruct); i++)
    {
        //Data.push_back(*Mat_VarGetStructFieldByIndex(topLevelStruct, i, 0));
                //cout << "check loop " << &Data.at(i) << " " << &topLevelStruct << endl;

        TopLevelStructFields[i] = *Mat_VarGetStructFieldByIndex(topLevelStruct, i, 0);
                        //cout << "check loop end" << endl;

    }
    
    //cout << "check " << Data[RAWDATA].dims[1] << " " << &Data[RAWDATA].dims[1] << endl;
        
    /* Reading all data structures that are present in the Data vector */
    
    /* Read raw data structure into a 2D vector. Format is RawData[column][row],
     * where column is mass or signal axis and row is the data index. */
    RawData.resize(TopLevelStructFields[RAWDATA].dims[1]);   //Data[RAWDATA].dims[1]
    //cout << "check " << RawData.size() << " " << Data[RAWDATA].dims[0] << endl;

    RawData[0].resize(TopLevelStructFields[RAWDATA].dims[0]);
    RawData[1].resize(TopLevelStructFields[RAWDATA].dims[0]);
    
    for(int i = 0; i < TopLevelStructFields[RAWDATA].dims[1]; i++)
    {
        for(int j = 0; j < TopLevelStructFields[RAWDATA].dims[0]; j++)
        {
            //cout << i << " " << j << " " << Mat_SizeOf(Data[DataFields::RAWDATA].data_type) << " dosiel" << endl;
            RawData[i][j] = *(double *)(TopLevelStructFields[RAWDATA].data + 8 * (i * TopLevelStructFields[RAWDATA].dims[0] + j));
            //RawData[i][j] = 0;
        }
    }
    
//    cout << "check" << endl;

    /* Read start index field */
    startInd = *(double *)(TopLevelStructFields[STARTIND].data);
    //cout << "hue " << startInd << endl;
    
    /* Read end index field */
    endInd = *(double *)(TopLevelStructFields[ENDIND].data);
    //cout << "bue " << endInd << endl;
    
//    cout << "check" << endl;

    /* Read molecules structure */
    MoleculesData.resize(TopLevelStructFields[MOLECULES].dims[1]);
    matvar_t moleculeField;    
        
    /* Iterating through all molecules, which are represented by a struct themselves. We are dealing with a struct of structs. */
    for(int i = 0; i < TopLevelStructFields[MOLECULES].dims[1]; i++)
    {
        /* Structure to hold molecule data is first created, then pushed into a vector. */
        Molecule_t molec;
        MoleculesData.push_back(molec);
        
        /* Iterating through all fields of a single molecule structure */
        for(int j = 0; j < Mat_VarGetNumberOfFields(&TopLevelStructFields[MOLECULES]); j++)
        {
            moleculeField = *Mat_VarGetStructFieldByIndex(&TopLevelStructFields[MOLECULES], j, i);
            
            /* Fields of a molecule are accessed by index, so their processing is also by index */
            switch(j)
            {
                case 0 :
                {
                    MoleculesData[i].PeakData.resize(moleculeField.dims[0]);
                    
                    for(int k = 0; k < moleculeField.dims[0]; k++)
                    {
                        MoleculesData[i].PeakData[k].resize(moleculeField.dims[1]);
                        
                        for(int l = 0; l < moleculeField.dims[1]; l++)
                        {
                            //cout << *(double *)(moleculeField.data + 8 * k + 8 * l * moleculeField.dims[0]) << endl;
                            MoleculesData[i].PeakData[k][l] = *(double *)(moleculeField.data + 8 * k + 8 * l * moleculeField.dims[0]);
                        }
                    }
                    break;
                }
                case 1 :
                {
                    for(int k = 0; k < moleculeField.dims[1]; k++)
                    {
                        MoleculesData[i].name += *(char *)(moleculeField.data + k);
                    }
                    break;
                }
                case 2 :
                {
                    MoleculesData[i].minMass = *(double *)(moleculeField.data);
                    //cout << "nazdar " << *(double *)(moleculeField.data) << endl;
                    break;
                }
                case 3 :
                {
                    MoleculesData[i].maxMass = *(double *)(moleculeField.data);
                    break;
                }
                case 4 :
                {
                    MoleculesData[i].com = *(double *)(moleculeField.data);
                    break;
                }
                case 5 :
                {
                    MoleculesData[i].minInd = *(double *)(moleculeField.data);
                    break;
                }
                case 6 :
                {
                    MoleculesData[i].maxInd = *(double *)(moleculeField.data);
                    break;
                }
                case 7 :
                {
                    MoleculesData[i].area = *(double *)(moleculeField.data);
                    break;
                }
                case 8 :
                {
                    MoleculesData[i].areaError = *(double *)(moleculeField.data);
                    //cout << "nazdar " << *(double *)(moleculeField.data) << endl;
                    break;
                }
                case 9 :
                {
                    MoleculesData[i].rootIndex = *(double *)(moleculeField.data);
                    break;
                }
            }
        }        
    }

    /* Memory management */
    //Mat_VarFree(&moleculeField);
    
    /* Read calibration struct */    
    matvar_t calibrationField;

    for(int i = 0; i < Mat_VarGetNumberOfFields(&TopLevelStructFields[CALIBRATION]); i++)
    {
        /* Gets subfield of the calibration struct */
        calibrationField = *Mat_VarGetStructFieldByIndex(&TopLevelStructFields[CALIBRATION], i, 0);
        //cout << "field name " << calibrationField.name << endl;
        
        /* Processes the field according to its index */
        switch(i)
        {
            case 0 :
            {
                //cout << "comlist size " << calibrationField.dims[0] << endl;
                CalibrationData.COMList.resize(calibrationField.dims[0]);

                for(int j = 0; j < calibrationField.dims[0]; j++)
                {
                    CalibrationData.COMList[j] = *(double *)(calibrationField.data + Mat_SizeOf(calibrationField.data_type) * j);
                    //cout << *(double *)(calibrationField.data + Mat_SizeOf(calibrationField.data_type) * j) << " " << CalibrationData.COMList[j] << endl;
                }
                break;
            }
            case 1 :
            {
                //cout << "massoffsetlist size " << calibrationField.dims[0] << endl;
                CalibrationData.MassOffsetList.resize(calibrationField.dims[0]);

                for(int j = 0; j < calibrationField.dims[0]; j++)
                {
                    CalibrationData.MassOffsetList[j] = *(double *)(calibrationField.data + Mat_SizeOf(calibrationField.data_type) * j);
                    //cout << *(double *)(calibrationField.data + Mat_SizeOf(calibrationField.data_type) * j) << " " << CalibrationData.MassOffsetList[j] << endl;
                }
                break;
            }
            case 2 :
            {
                //cout << "resolutionlist size " << calibrationField.dims[0] << endl;
                CalibrationData.ResolutionList.resize(calibrationField.dims[0]);

                for(int j = 0; j < calibrationField.dims[0]; j++)
                {
                    CalibrationData.ResolutionList[j] = *(double *)(calibrationField.data + Mat_SizeOf(calibrationField.data_type) * j);
                    //cout << *(double *)(calibrationField.data + Mat_SizeOf(calibrationField.data_type) * j) << " " << CalibrationData.ResolutionList[j] << endl;
                }
                break;
            }
            case 3 :
            {
                for(int j = 0; j < calibrationField.dims[1]; j++)
                {
                    CalibrationData.MassOffsetMethod += *(char *)(calibrationField.data + j);
                }
                break;
            }
            case 4 :
            {
                for(int j = 0; j < calibrationField.dims[1]; j++)
                {
                    CalibrationData.ResolutionMethod += *(char *)(calibrationField.data + j);
                }
                break;
            }
            case 5 :
            {
                CalibrationData.massOffsetParam = *(double *)(calibrationField.data);
                break;
            }
            case 6 :
            {
                CalibrationData.resolutionParam = *(double *)(calibrationField.data);
                break;
            }
            case 7 :
            {
//                cout << "namelist size " << calibrationField.dims[1] << endl;
//                cout << "namelist size before " << CalibrationData.NameList.size() << endl;
                CalibrationData.NameList.resize(calibrationField.dims[1]);
//                cout << "namelist size after " << CalibrationData.NameList.size() << endl;
                matvar_t namelistField;
                
                for(int j = 0; j < calibrationField.dims[1]; j++)
                {
                    namelistField = *Mat_VarGetCell(&calibrationField, j);
                    
//                    cout << "nameliststringsize " << namelistField.dims[1] << endl;
                    for(int k = 0; k < namelistField.dims[1]; k++)
                    {
                        CalibrationData.NameList[j] += *(char *)(namelistField.data + k);
//                        cout << *(char *)(namelistField.data + k);
                    }
//                    cout << endl;
//                    cout << CalibrationData.NameList[j] << endl;
                }
                break;
            }
            case 8 :
            {
                /* This subfield is a struct. Structception. Same prodecure for processing its subfields. */
                matvar_t shapeField;

                for(int k = 0; k < Mat_VarGetNumberOfFields(&calibrationField); k++)
                {
                    shapeField = *Mat_VarGetStructFieldByIndex(&calibrationField, k, 0);
                    
                    switch(k)
                    {
                        case 0 :
                        {
                            for(int l = 0; l < shapeField.dims[1]; l++)
                            {
                                CalibrationData.Shape.form += *(char *)(shapeField.data + l);
                            }
                            //cout << CalibrationData.Shape.form << endl;
                            break;
                        }
                        case 1 :
                        {
                            CalibrationData.Shape.Breaks.resize(shapeField.dims[1]);
                            
                            for(int l = 0; l < shapeField.dims[1]; l++)
                            {
                                CalibrationData.Shape.Breaks[l] = *(double *)(shapeField.data + Mat_SizeOf(shapeField.data_type) * l);
                                //cout << CalibrationData.Shape.Breaks[l] << endl;
                            }
                            break;
                        }
                        case 2 :
                        {
                            CalibrationData.Shape.Coefs.resize(shapeField.dims[0]);
                            
                            for(int l = 0; l < shapeField.dims[0]; l++)
                            {
                                CalibrationData.Shape.Coefs[l].resize(shapeField.dims[1]);
                                
                                for(int m = 0; m < shapeField.dims[1]; m++)
                                {
                                    //cout << "index " << Mat_SizeOf(shapeField.data_type) * m + Mat_SizeOf(shapeField.data_type) * l * shapeField.dims[0] << endl;
                                    CalibrationData.Shape.Coefs[l][m] = *(double *)(shapeField.data + Mat_SizeOf(shapeField.data_type) * l + Mat_SizeOf(shapeField.data_type) * m * shapeField.dims[0]);
                                    //cout << CalibrationData.Shape.Coefs[l][m] << endl;
                                }
                            }
                            break;
                        }
                        case 3 :
                        {
                            CalibrationData.Shape.pieces = *(double *)(shapeField.data);
                            //cout << CalibrationData.Shape.pieces << endl;
                            break;
                        }
                        case 4 :
                        {
                            CalibrationData.Shape.order = *(double *)(shapeField.data);
                            //cout << CalibrationData.Shape.order << endl;
                            break;
                        }
                        case 5 :
                        {
                            CalibrationData.Shape.dim = *(double *)(shapeField.data);
                            //cout << CalibrationData.Shape.dim << endl;
                            break;
                        }
                    }
                }
                break;
                
                /* Memory management */    
                //Mat_VarFree(&shapeField);
            }
        }
    }
    
    /* Memory management */    
    //Mat_VarFree(&calibrationField);
    
    /* Read background correction data */
    matvar_t BgCorrField;

    for(int i = 0; i < Mat_VarGetNumberOfFields(&TopLevelStructFields[BGCORRECTIONDATA]); i++)
    {
        BgCorrField = *Mat_VarGetStructFieldByIndex(&TopLevelStructFields[BGCORRECTIONDATA], i, 0);
        
        switch(i)
        {
            case 0 :
            {
                //CalibrationData.Shape.pieces = *(double *)(shapeField.data);
                BGCorrectionData.startMass = *(double *)(BgCorrField.data);
                //cout << "startmass " <<BGCorrectionData.startMass << endl;                
                //cout << CalibrationData.Shape.form << endl;
                break;
            }
            case 1 :
            {
                BGCorrectionData.endMass = *(double *)(BgCorrField.data);
                //cout << "endmass " <<BGCorrectionData.endMass << endl;                
                break;
            }
            case 2 :
            {
                BGCorrectionData.nDiv = *(double *)(BgCorrField.data);
                //cout << "ndiv " << BGCorrectionData.nDiv << endl;
                break;
            }
            case 3 :
            {
                
                BGCorrectionData.percent = *(double *)(BgCorrField.data);                
                //cout << CalibrationData.Shape.pieces << endl;
                //cout << "percent " << BGCorrectionData.percent << endl;
                break;
            }
            case 4 :
            {
                //CalibrationData.Shape.Coefs.resize(shapeField.dims[0]);
                BGCorrectionData.Bgm.resize(BgCorrField.dims[0]);

                for(int j = 0; j < BgCorrField.dims[0]; j++)
                {
                    //cout << "index " << Mat_SizeOf(shapeField.data_type) * m + Mat_SizeOf(shapeField.data_type) * l * shapeField.dims[0] << endl;
                    //CalibrationData.Shape.Coefs[l][m] = *(double *)(shapeField.data + Mat_SizeOf(shapeField.data_type) * l + Mat_SizeOf(shapeField.data_type) * m * shapeField.dims[0]);
                    //cout << CalibrationData.Shape.Coefs[l][m] << endl;
                    BGCorrectionData.Bgm[j] = *(double *)(BgCorrField.data + Mat_SizeOf(BgCorrField.data_type) * j);
                    //cout << "bgm " << BGCorrectionData.Bgm[j] << endl;
                }
                
//                CalibrationData.Shape.pieces = *(double *)(shapeField.data);
//                CalibrationData.Shape.order = *(double *)(shapeField.data);
                //cout << CalibrationData.Shape.order << endl;
                break;
            }
            case 5 :
            {
                BGCorrectionData.Bgy.resize(BgCorrField.dims[0]);

                for(int j = 0; j < BgCorrField.dims[0]; j++)
                {
                    //cout << "index " << Mat_SizeOf(shapeField.data_type) * m + Mat_SizeOf(shapeField.data_type) * l * shapeField.dims[0] << endl;
                    //CalibrationData.Shape.Coefs[l][m] = *(double *)(shapeField.data + Mat_SizeOf(shapeField.data_type) * l + Mat_SizeOf(shapeField.data_type) * m * shapeField.dims[0]);
                    //cout << CalibrationData.Shape.Coefs[l][m] << endl;
                    BGCorrectionData.Bgy[j] = *(double *)(BgCorrField.data + Mat_SizeOf(BgCorrField.data_type) * j);
                    //cout << "bgy " << BGCorrectionData.Bgy[j] << endl;
                }
                //cout << CalibrationData.Shape.dim << endl;
                break;
            }
        }
    }
    
    /* Memory management */    
    //Mat_VarFree(&BgCorrField);
    
    /* Read GUI status vector */    
    GUIStatus.resize(TopLevelStructFields[GUISTATUSVECTOR].dims[1]);

    for(int i = 0; i < TopLevelStructFields[GUISTATUSVECTOR].dims[1]; i++)
    {
        //TODO: read as booleans
        GUIStatus[i] = *(double *)(TopLevelStructFields[GUISTATUSVECTOR].data + Mat_SizeOf(TopLevelStructFields[GUISTATUSVECTOR].data_type) * i);
        //cout << "gui " << GUIStatus[i] << endl;
    }

    /* Read file info */
    matvar_t FileInfoField;
    
    for(int i = 0; i < Mat_VarGetNumberOfFields(&TopLevelStructFields[FILEINFO]); i++)
    {
        FileInfoField = *Mat_VarGetStructFieldByIndex(&TopLevelStructFields[FILEINFO], i, 0);
        
        switch(i)
        {
            case 0 :
            {
                for(int j = 0; j < FileInfoField.dims[1]; j++)
                {
                    FileInfoData.originalFileName += *(char *)(FileInfoField.data + j);
                }
                //cout << "filename " << FileInfoData.originalFileName << endl;           
                break;
            }
            case 1 :
            {
                for(int j = 0; j < FileInfoField.dims[1]; j++)
                {
                    FileInfoData.fileName += *(char *)(FileInfoField.data + j);
                }
                //cout << "filename " << FileInfoData.fileName << endl;                
                break;
            }
            case 2 :
            {
                for(int j = 0; j < FileInfoField.dims[1]; j++)
                {
                    FileInfoData.pathName += *(char *)(FileInfoField.data + j);
                }
                //cout << "filename " << FileInfoData.pathName << endl;           
                break;
            }
            case 3 :
            {
                
                for(int j = 0; j < FileInfoField.dims[1]; j++)
                {
                    FileInfoData.h5CompletePath += *(char *)(FileInfoField.data + j);
                }
                //cout << "filename " << FileInfoData.h5CompletePath << endl;           
                break;
            }
        }
    }
        
    /* Close the file. It also frees memory. */
    Mat_Close(file);
}