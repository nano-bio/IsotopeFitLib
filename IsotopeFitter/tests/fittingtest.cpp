/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fittingtest.cpp
 * Author: matlab
 *
 * Created on October 11, 2016, 7:46 PM
 */

#include <stdlib.h>
#include <iostream>

#include "src/IsotopeFitter.h"
#include <fstream>

#include <gsl/gsl_fit.h>
#include <gsl/gsl_spline.h>

/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "fittingtest test 1" << std::endl;
    
    /* Load data */
    string str = "/home/matlab/Michal/dev/IsotopeFitter/tests/testfileifd2.ifd";
    LoadIFDFile(str);
    
    vector<double> Baseline;
    Baseline.resize(IFData::RawData[0].size());
    
    FitBaseline(IFData::BGCorrectionData.Bgm, IFData::BGCorrectionData.Bgy, IFData::RawData[0], Baseline);
    
    ofstream bgdata, bgfit;
    
    bgdata.open("bgdata");
    
    for(int i = 0; i < IFData::BGCorrectionData.Bgm.size(); i++)
    {
        //cout << IFData::BGCorrectionData.Bgm[i] << " " << IFData::BGCorrectionData.Bgy[i] << endl;
        bgdata << IFData::BGCorrectionData.Bgm[i] << " " << IFData::BGCorrectionData.Bgy[i] << endl;
    }
//    cout << endl;
    bgdata.close();
    
    bgfit.open("bgfit");
    
    for(int i = 0; i < IFData::RawData[0].size(); i++)
    {
        //cout << IFData::RawData[0][i] << " " << Baseline[i] << endl;
        bgfit << IFData::RawData[0][i] << " " << Baseline[i] << endl;
    }
//    cout << endl;
    bgfit.close();
}

void test2() {
    std::cout << "fittingtest test 2" << std::endl;
    
    /* Load data */
    string str = "/home/matlab/Michal/dev/IsotopeFitter/tests/testfileifd2.ifd";
    LoadIFDFile(str);
    
    double c0, c1;
    
    FitResolution(IFData::CalibrationData.COMList, IFData::CalibrationData.ResolutionList, 0, c0, c1);
    
    ofstream resfit;    
    resfit.open("resfit");
    
    for(int i = 0; i < IFData::CalibrationData.COMList.size(); i++)
    {
        //cout << IFData::RawData[0][i] << " " << Baseline[i] << endl;
        resfit << IFData::CalibrationData.COMList[i] << " " << IFData::CalibrationData.ResolutionList[i] << endl;
    }
//    cout << endl;
    resfit.close();
    
    cout << c0 << " " << c1 << endl;
}

void test3() {
    std::cout << "fittingtest test 3" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (fittingtest) message=error message sample" << std::endl;
    
    /* Load data */
    string str = "/home/matlab/Michal/dev/IsotopeFitter/tests/testfileifd2.ifd";
    LoadIFDFile(str);
    
    vector<double> MassAxisCorr;
    MassAxisCorr.resize(IFData::RawData[0].size());
    
    FitMassOffsets(IFData::CalibrationData.COMList, IFData::CalibrationData.MassOffsetList, 0, IFData::RawData[0], MassAxisCorr);
    
    ofstream massoffsetdata, massoffsetfit;
    
    massoffsetdata.open("massoffsetdata");
    
    for(int i = 0; i < IFData::CalibrationData.COMList.size(); i++)
    {
        //cout << IFData::CalibrationData.COMList[i] << " " << IFData::CalibrationData.MassOffsetList[i] << endl;
        massoffsetdata << IFData::CalibrationData.COMList[i] << " " << IFData::CalibrationData.MassOffsetList[i] << endl;
    }
//    cout << endl;
    massoffsetdata.close();
    
    massoffsetfit.open("massoffsetfit");
    
    for(int i = 0; i < IFData::RawData[0].size(); i++)
    {
        //cout << IFData::RawData[0][i] << " " << Baseline[i] << endl;
        massoffsetfit << IFData::RawData[0][i] << " " << MassAxisCorr[i] << " " << IFData::RawData[1][i] << endl;
    }
    
    //TODO: something is wrong
//    cout << endl;
    massoffsetfit.close();
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% fittingtest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

//    std::cout << "%TEST_STARTED% test1 (fittingtest)" << std::endl;
//    test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (fittingtest)" << std::endl;

//    std::cout << "%TEST_STARTED% test2 (fittingtest)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (fittingtest)" << std::endl;
    
    std::cout << "%TEST_STARTED% test3 (fittingtest)" << std::endl;
    test3();
    std::cout << "%TEST_FINISHED% time=0 test3 (fittingtest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

