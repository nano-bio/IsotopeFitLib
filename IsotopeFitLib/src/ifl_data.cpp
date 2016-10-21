/**
 * IsotopeFitLib
 * ifl_data.cpp
 * 
 * @author Michal Durian
 * @version 21.10.2016 16:05 MD
 * 
 * Changes log:
 * 
 */

#include "../include/ifl_data.h"

using namespace std;

/* Utility function that prints samples of data from a loaded IFD file, to see if it correct. */
void PrintLoadedData()
{
    cout << "RawData" << endl;
    for (int i=0; i<10; i++)
    {
        cout << IFData::RawData[0][i] << " " << IFData::RawData[1][i] << " " << endl;
    }
    cout << endl;
    
    cout << "startInd" << endl;
    cout << IFData::startInd << endl;
    cout << endl;
    
    cout << "endInd" << endl;
    cout << IFData::endInd << endl;
    cout << endl;
    
    cout << "Molecules" << endl;
    for (int i=0; i<10; i++)
    {
        cout << "peak data" << endl;        
        for(int k = 0; k < IFData::MoleculesData[i].PeakData.size(); k++)
        {
            for(int l = 0; l < IFData::MoleculesData[i].PeakData[k].size(); l++)
            {
                cout << IFData::MoleculesData[i].PeakData[k][l] << " ";
            }
            cout << endl;
        }
        
        cout << "name " << IFData::MoleculesData[i].name << endl;
        cout << "minMass " << IFData::MoleculesData[i].minMass << endl;
        cout << "maxMass " << IFData::MoleculesData[i].maxMass << endl;
        cout << "com " << IFData::MoleculesData[i].com << endl;
        cout << "minInd " << IFData::MoleculesData[i].minInd << endl;
        cout << "maxInd " << IFData::MoleculesData[i].maxInd << endl;
        cout << "area " << IFData::MoleculesData[i].area << endl;
        cout << "areaError " << IFData::MoleculesData[i].areaError << endl;
        cout << "rootIndex " << IFData::MoleculesData[i].rootIndex << endl;
        cout << endl;
    }
    
    cout << "Calibration" << endl;

    cout << "comlist" << endl;
    for (int j=0; j<10; j++)
    {
        cout << IFData::CalibrationData.COMList[j] << endl;
    }

    cout << "MassOffsetList" << endl;
    for (int j=0; j<10; j++)
    {
        cout << IFData::CalibrationData.MassOffsetList[j] << endl;
    }

    cout << "ResolutionList" << endl;
    for (int j=0; j<10; j++)
    {
        cout << IFData::CalibrationData.ResolutionList[j] << endl;
    }
    cout << "MassOffsetMethod " << IFData::CalibrationData.MassOffsetMethod << endl;
    cout << "ResolutionMethod " << IFData::CalibrationData.ResolutionMethod << endl;
    cout << "massOffsetParam " << IFData::CalibrationData.massOffsetParam << endl;
    cout << "resolutionParam " << IFData::CalibrationData.resolutionParam << endl;
    cout << "NameList" << endl;
    for (int j=0; j<10; j++)
    {
        cout << IFData::CalibrationData.NameList[j] << endl;
    }
    cout << endl;
        
    cout << "Shape" << endl;
    cout << "form " << IFData::CalibrationData.Shape.form << endl;
    cout << "Breaks " << endl;
    for (int j=0; j<10; j++)
    {
        cout << IFData::CalibrationData.Shape.Breaks[j] << endl;
    }    
    cout << "Coefs " << endl;
    for (int j=0; j<IFData::CalibrationData.Shape.Coefs.size(); j++)
    {
        for (int k=0; k<IFData::CalibrationData.Shape.Coefs[j].size(); k++)
        {
            cout << IFData::CalibrationData.Shape.Coefs[j][k] << "\t";
        }
        cout << endl;
    }    
    cout << "pieces " << IFData::CalibrationData.Shape.pieces << endl;
    cout << "order " << IFData::CalibrationData.Shape.order << endl;    
    cout << "dim " << IFData::CalibrationData.Shape.dim << endl;
    cout << endl;

    cout << "bgcorrection " << endl;
    cout << "startMass " << IFData::BGCorrectionData.startMass << endl;
    cout << "endMass " << IFData::BGCorrectionData.endMass << endl;
    cout << "nDiv " << IFData::BGCorrectionData.nDiv << endl;
    cout << "percent " << IFData::BGCorrectionData.percent << endl;
    
    cout << "Bgm " << endl;
    for (int j=0; j<10; j++)
    {
        cout << IFData::BGCorrectionData.Bgm[j] << endl;
    }    
    cout << "Bgy " << endl;
    for (int j=0; j<10; j++)
    {
        cout << IFData::BGCorrectionData.Bgy[j] << endl;
    }    
    cout << endl;

    cout << "gui " << endl;
    for (int j=0; j<IFData::GUIStatus.size(); j++)
    {
        cout << IFData::GUIStatus[j] << endl;
    }    
    cout << endl;

    cout << "originalFileName " << IFData::FileInfoData.originalFileName << endl;
    cout << "fileName " << IFData::FileInfoData.fileName << endl;
    cout << "pathName " << IFData::FileInfoData.pathName << endl;
    cout << "h5CompletePath " << IFData::FileInfoData.h5CompletePath << endl;
    cout << endl;
}