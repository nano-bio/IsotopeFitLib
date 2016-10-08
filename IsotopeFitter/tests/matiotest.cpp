/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   matiotest.cpp
 * Author: matlab
 *
 * Created on October 4, 2016, 10:26 PM
 */

#include <stdlib.h>
#include <iostream>

#include "src/IsotopeFitter.h"

using namespace std;

void test1() {
    std::cout << "matiotest test 1" << std::endl;
    
    string str = "tests/testfileifd.ifd";
    
    mat_t *file;
    
    file = Mat_Open(str.c_str(), MAT_ACC_RDONLY);
    
    matvar_t *var;
    
    var = Mat_VarReadInfo(file, "data");
    
    if (var == NULL)
    {
        cout << "var is null" << endl;
    }
    
    std::cout << "pointer " << var << std::endl;
    std::cout << "class type " << var->class_type << std::endl;
    std::cout << "data size " << var->data_size << std::endl;
    std::cout << "data type " << var->data_type << std::endl;
    std::cout << "name " << var->name << std::endl;
    std::cout << "dims " << var->dims[0] << " " << var->dims[1] << std::endl;
    std::cout << "rank " << var->rank << std::endl;
    std::cout << "data " << var->data << std::endl;
    std::cout << std::endl;

    matvar_t *var2;
    
    var2 = Mat_VarRead(file, "data");
    
    std::cout << "pointer " << var2 << std::endl;    
    std::cout << "class type " << var2->class_type << std::endl;
    std::cout << "compression " << var2->compression << std::endl;
    std::cout << "data " << var2->data << std::endl;
    std::cout << "data size " << var2->data_size << std::endl;
    std::cout << "data type " << var2->data_type << std::endl;
    std::cout << "dims " << var2->dims << " " << var2->dims[0] << " " << var2->dims[1] << std::endl;
    std::cout << "internal " << var2->internal << std::endl;
    std::cout << "complex " << var2->isComplex << std::endl;
    std::cout << "global " << var2->isGlobal << std::endl;
    std::cout << "logical " << var2->isLogical << std::endl;
    std::cout << "mem conserve " << var2->mem_conserve << std::endl;
    std::cout << "name " << var2->name << std::endl;
    std::cout << "nbytes " << var2->nbytes << std::endl;
    std::cout << "rank " << var2->rank << std::endl;
    std::cout << std::endl;

    //std::cout << "element 0 " << var2[1].data_type << std::endl;
    char *const *fields;
    fields = Mat_VarGetStructFieldnames(var);
    
    cout << *(fields+1) << endl;
    cout << Mat_VarGetStructFieldByIndex(var, 1, 0)->data_type << endl;
//    std::cout << std::endl;
//    void *var2 = var->data;
//    
//    std::cout << "pointer " << var2 << std::endl;
//    
//    matvar_t var3 = *(matvar_t *)(var2);
//    std::cout << "pointer " << var3 << std::endl;
//    std::cout << "class type " << var3.class_type << std::endl;
//    std::cout << "data size " << var3.data_size << std::endl;
//    std::cout << "data type " << var3.data_type << std::endl;
//    std::cout << "name " << var3.name << std::endl;
//    std::cout << "dims " << var3.dims[0] << " " << var->dims[1] << std::endl;
//    std::cout << "rank " << var3.rank << std::endl;
//    std::cout << "data " << var3.data << std::endl;
    
    //std::cout << "element " << var2[0] << std::endl;

    
    //matvar_t *var2;
    //var2 = var->data;
    //std::cout << "pointer " << var2 << std::endl;

    //cout << var(0).field1 << endl;
    
//    matvar_t *var2;
//    var2 = Mat_VarReadInfo(var, "data");
//
//    if (var2 == NULL)
//    {
//        cout << "var2 is null" << endl;
//    }
    
    Mat_VarFree(var);
//    Mat_VarFree(var2);
    
    Mat_Close(file);
}

void test2() {
    std::cout << "matiotest test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (matiotest) message=error message sample" << std::endl;
    
    //OpenIFDFileRD("tests/testfileifd.ifd");
    string str = "tests/testfileifd.ifd";
    
    LoadIFDFile(str);
    
//    for(int i=0; i<VariablesInfo.size(); i++)
//    {
//        cout << VariablesInfo.at(i).class_type << endl;
//    }
    
    cout << endl;
    
//    for(int i=0; i<Variables.size(); i++)
//    {
//        cout << Variables.at(i).name << endl;
//    }
    
//    for(int i=0; i<VariablesInfo.at(0).data_size; i++)
//    {
//        cout << *(StructFields+i) << endl;
//    }
    
//    for(int i=0; i<Data.size(); i++)
//    {
//        cout << Data[i].name << endl;
//    }
    
    cout << endl;
    //std::cout << "pointer " << Data[0] << std::endl;    
//    std::cout << "class type " << Data[0].class_type << std::endl;
//    std::cout << "compression " << Data[0].compression << std::endl;
//    std::cout << "data " << Data[0].data << std::endl;
//    std::cout << "data size " << Data[0].data_size << std::endl;
//    std::cout << "data type " << Data[0].data_type << std::endl;
//    std::cout << "dims " << Data[0].dims << " " << Data[0].dims[0] << " " << Data[0].dims[1] << std::endl;
//    std::cout << "internal " << Data[0].internal << std::endl;
//    std::cout << "complex " << Data[0].isComplex << std::endl;
//    std::cout << "global " << Data[0].isGlobal << std::endl;
//    std::cout << "logical " << Data[0].isLogical << std::endl;
//    std::cout << "mem conserve " << Data[0].mem_conserve << std::endl;
//    std::cout << "name " << Data[0].name << std::endl;
//    std::cout << "nbytes " << Data[0].nbytes << std::endl;
//    std::cout << "rank " << Data[0].rank << std::endl;
    
    //Mat_VarReadData(mat_t *mat,matvar_t *matvar,void *data, int *start,int *stride,int *edge);
    double arr [3] = { 1.234, 5.678, 9.012 };
    
    void *out = &arr;
    
    cout << arr << endl;
    cout << &arr << endl;
    cout << arr[0] << endl;
    cout << &arr[0] << endl;
    cout << out << endl;
    cout << (*(double*)(out)) << endl;
}

void test3() {
    std::cout << "matiotest test 3" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (matiotest) message=error message sample" << std::endl;
    
    string str = "tests/testfileifd.ifd"; 
     
    mat_t *file;    
    file = Mat_Open(str.c_str(), MAT_ACC_RDONLY);
    
    matvar_t *var;    
    var = Mat_VarRead(file, "data");
    
    std::cout << std::endl;
    std::cout << "pointer " << var << std::endl;    
    std::cout << "class type " << var->class_type << std::endl;
    std::cout << "compression " << var->compression << std::endl;
    std::cout << "data " << var->data << std::endl;
    std::cout << "data size " << var->data_size << std::endl;
    std::cout << "data type " << var->data_type << std::endl;
    std::cout << "dims " << var->dims << " " << var->dims[0] << " " << var->dims[1] << std::endl;
    std::cout << "internal " << var->internal << std::endl;
    std::cout << "complex " << var->isComplex << std::endl;
    std::cout << "global " << var->isGlobal << std::endl;
    std::cout << "logical " << var->isLogical << std::endl;
    std::cout << "mem conserve " << var->mem_conserve << std::endl;
    std::cout << "name " << var->name << std::endl;
    std::cout << "nbytes " << var->nbytes << std::endl;
    std::cout << "rank " << var->rank << std::endl;
    std::cout << std::endl;
    
    //matvar_t  *Mat_VarSetStructFieldByIndex(matvar_t *matvar, size_t field_index,size_t index,matvar_t *field);
    matvar_t *var2; 
    var2 = Mat_VarGetStructFieldByIndex(var, 0, 0);
    
    std::cout << std::endl;
    std::cout << "pointer " << var2 << std::endl;    
    std::cout << "class type " << var2->class_type << std::endl;
    std::cout << "compression " << var2->compression << std::endl;
    std::cout << "data " << var2->data << std::endl;
    std::cout << "data size " << var2->data_size << std::endl;
    std::cout << "data type " << var2->data_type << std::endl;
    std::cout << "dims " << var2->dims << " " << var2->dims[0] << " " << var2->dims[1] << std::endl;
    std::cout << "internal " << var2->internal << std::endl;
    std::cout << "complex " << var2->isComplex << std::endl;
    std::cout << "global " << var2->isGlobal << std::endl;
    std::cout << "logical " << var2->isLogical << std::endl;
    std::cout << "mem conserve " << var2->mem_conserve << std::endl;
    std::cout << "name " << var2->name << std::endl;
    std::cout << "nbytes " << var2->nbytes << std::endl;
    std::cout << "rank " << var2->rank << std::endl;
    std::cout << std::endl;
    
    cout << var2->nbytes / var2->data_size << endl;
    
    cout << *(double*)(var2->data+8*400000) << endl;
    
    //Mat_VarReadData(mat_t *mat,matvar_t *matvar,void *data, int *start,int *stride,int *edge);
    //void *out;
    vector<double> outDoub;
    outDoub.resize(var2->dims[0] * var2->dims[1]);
    
    double ptr[var2->dims[0] * var2->dims[1]];
    
    int start[2] = {0,0};
    int stride[2] = {8,1};
    int edge[2] = {4996000, 2 };
    
    //std::cout << &start << std::endl;
    
    int res;
    res = Mat_VarReadData(file, var2, ptr, start, stride, edge);
    std::cout << std::endl;
    cout << "read data " << res << endl;
    std::cout << std::endl;
    
    cout << "start " << start[0] << " " << start[1] << endl;
    cout << "stride " << stride[0] << " " << stride[1] << endl;
    cout << "edge " << edge[0] << " " << edge[1] << endl;
    
    printf("%f", ptr[2*312250-1]);
    
//    cout << out << endl;
//    cout << *(double *)(out+100) << endl;
    //cout << outDoub[0] << endl;
    std::cout << std::endl;

//    for(int i=0; i<100; i++)
//    {
//        //cout << static_cast<short>(*(uint8_t *)(out+i)) << endl;
//        cout << ptr[0] << endl;
//    }
}

void test4() {
    std::cout << "matiotest test 4" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (matiotest) message=error message sample" << std::endl;
    
    string str = "tests/testfileifd.ifd";
    LoadIFDFile(str);
    
    cout << "RawData" << endl;
    for (int i=0; i<10; i++)
    {
        cout << RawData[0][i] << " " << RawData[1][i] << " " << endl;
    }
    cout << endl;
    
    cout << "startInd" << endl;
    cout << startInd << endl;
    cout << endl;
    
    cout << "endInd" << endl;
    cout << endInd << endl;
    cout << endl;
    
    cout << "Molecules" << endl;
    for (int i=0; i<10; i++)
    {
        cout << "peak data" << endl;
//        for (int j=0; j<MoleculesData[i].PeakData.size(); j++)
//        {
//            cout << MoleculesData[i].PeakData[j] << endl;
//        }
        
        for(int k = 0; k < MoleculesData[i].PeakData.size(); k++)
        {
            for(int l = 0; l < MoleculesData[i].PeakData[k].size(); l++)
            {
                cout << MoleculesData[i].PeakData[k][l] << " ";
                //*(double *)(shapeField.data + Mat_SizeOf(shapeField.data_type) * l + Mat_SizeOf(shapeField.data_type) * m * shapeField.dims[0]);
            }
            cout << endl;
        }
        
        cout << "name " << MoleculesData[i].name << endl;
        cout << "minMass " << MoleculesData[i].minMass << endl;
        cout << "maxMass " << MoleculesData[i].maxMass << endl;
        cout << "com " << MoleculesData[i].com << endl;
        cout << "minInd " << MoleculesData[i].minInd << endl;
        cout << "maxInd " << MoleculesData[i].maxInd << endl;
        cout << "area " << MoleculesData[i].area << endl;
        cout << "areaError " << MoleculesData[i].areaError << endl;
        cout << "rootIndex " << MoleculesData[i].rootIndex << endl;
        cout << endl;
    }
    
    cout << "Calibration" << endl;

    cout << "comlist" << endl;
    for (int j=0; j<10; j++)
    {
        cout << CalibrationData.COMList[j] << endl;
    }

    cout << "MassOffsetList" << endl;
    for (int j=0; j<10; j++)
    {
        cout << CalibrationData.MassOffsetList[j] << endl;
    }

    cout << "ResolutionList" << endl;
    for (int j=0; j<10; j++)
    {
        cout << CalibrationData.ResolutionList[j] << endl;
    }
    cout << "MassOffsetMethod " << CalibrationData.MassOffsetMethod << endl;
    cout << "ResolutionMethod " << CalibrationData.ResolutionMethod << endl;
    cout << "massOffsetParam " << CalibrationData.massOffsetParam << endl;
    cout << "resolutionParam " << CalibrationData.resolutionParam << endl;

    cout << "NameList" << endl;
    for (int j=0; j<10; j++)
    {
        cout << CalibrationData.NameList[j] << endl;
    }
    cout << endl;
        
    cout << "Shape" << endl;
    cout << "form " << CalibrationData.Shape.form << endl;
    cout << "Breaks " << endl;
    for (int j=0; j<10; j++)
    {
        cout << CalibrationData.Shape.Breaks[j] << endl;
    }
    
    cout << "Coefs " << endl;
    for (int j=0; j<CalibrationData.Shape.Coefs.size(); j++)
    {
        for (int k=0; k<CalibrationData.Shape.Coefs[j].size(); k++)
        {
            cout << CalibrationData.Shape.Coefs[j][k] << "\t";
        }
        cout << endl;
    }
    
    cout << "pieces " << CalibrationData.Shape.pieces << endl;

    cout << "order " << CalibrationData.Shape.order << endl;
    
    cout << "dim " << CalibrationData.Shape.dim << endl;

    
    
//    string form;
//    vector<double> Breaks;
//    vector<vector<double>> Coefs;
//    double pieces;
//    double order;
//    double dim;
        
//        vector<double> COMList;
//        vector<double> MassOffsetList;
//        vector<double> ResolutionList;
//        string MassOffsetMethod;
//        string ResolutionMethod;
//        double massOffsetParam;
//        double resolutionParam;
//        vector<string> NameList;
//        Shape_t Shape;

    cout << endl;

    cout << "bgcorrection " << endl;
    cout << "startMass " << BGCorrectionData.startMass << endl;
    cout << "endMass " << BGCorrectionData.endMass << endl;
    cout << "nDiv " << BGCorrectionData.nDiv << endl;
    cout << "percent " << BGCorrectionData.percent << endl;

    cout << "Bgm " << endl;
    for (int j=0; j<10; j++)
    {
        cout << BGCorrectionData.Bgm[j] << endl;
    }
    
    cout << "Bgy " << endl;
    for (int j=0; j<10; j++)
    {
        cout << BGCorrectionData.Bgy[j] << endl;
    }
    
            cout << endl;

    cout << "gui " << endl;
    for (int j=0; j<GUIStatus.size(); j++)
    {
        cout << GUIStatus[j] << endl;
    }
    
    cout << endl;

    cout << "originalFileName " << FileInfoData.originalFileName << endl;
    cout << "fileName " << FileInfoData.fileName << endl;
    cout << "pathName " << FileInfoData.pathName << endl;
    cout << "h5CompletePath " << FileInfoData.h5CompletePath << endl;
    cout << endl;

//    string originalFileName;
//    string fileName;
//    string pathName;
//    string h5CompletePath;
    
//    double startMass;
//    double endMass;
//    double nDiv;
//    double percent;
//    vector<double> Bgm;
//    vector<double> Bgy;
    
    
//    cout << "Molecules" << endl;
//    for (int i=0; i<10; i++)
//    {
//        //cout << MoleculesData[i].PeakData.size() << endl;
//        
//        for (int j=0; j<MoleculesData[i].PeakData.size(); j++)
//        {
//            cout << MoleculesData[i].PeakData[j] << endl;
//        }
//        
//        cout << "name " << MoleculesData[i].name << endl;
//        cout << "minmass " << MoleculesData[i].minMass << endl;
//        cout << "maxmass " << MoleculesData[i].maxMass << endl;
//        cout << "com " << MoleculesData[i].com << endl;
//        cout << "minind " << MoleculesData[i].minInd << endl;
//        cout << "maxind " << MoleculesData[i].maxInd << endl;
//        cout << "area " << MoleculesData[i].area << endl;
//        cout << "areaerror " << MoleculesData[i].areaError << endl;
//        cout << "rootindex " << MoleculesData[i].rootIndex << endl;
//    }
//    cout << endl;


}

void test5() {
    std::cout << "matiotest test 4" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (matiotest) message=error message sample" << std::endl;
    
    for (int i=0; i<10; i++)
    {
        string str = "tests/testfileifd.ifd";
        LoadIFDFile(str);
    }
    
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% matiotest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

//    std::cout << "%TEST_STARTED% test1 (matiotest)" << std::endl;
//    test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (matiotest)" << std::endl;

//    std::cout << "%TEST_STARTED% test2 (matiotest)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (matiotest)" << std::endl;
    
//    std::cout << "%TEST_STARTED% test3 (matiotest)\n" << std::endl;
//    test3();
//    std::cout << "%TEST_FINISHED% time=0 test3 (matiotest)" << std::endl;
    
    std::cout << "%TEST_STARTED% test4 (matiotest)\n" << std::endl;
    test4();
    std::cout << "%TEST_FINISHED% time=0 test4 (matiotest)" << std::endl;

//    std::cout << "%TEST_STARTED% test5 (matiotest)\n" << std::endl;
//    test5();
//    std::cout << "%TEST_FINISHED% time=0 testť (matiotest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

/* Random crapload of test code */
//char *const *calibFields = Mat_VarGetStructFieldnames(&Data[DataFields::CALIBRATION]);
//    matvar_t bgcorr;
//    
//    for(int i = 0; i < Mat_VarGetNumberOfFields(&Data[DataFields::BGCORRECTIONDATA]); i++)
//    {
//        bgcorr = *Mat_VarGetStructFieldByIndex(&Data[DataFields::BGCORRECTIONDATA], i, 0);
//        cout << endl;
//        std::cout << "class type " << bgcorr.class_type << std::endl;
//        std::cout << "compression " << bgcorr.compression << std::endl;
//        std::cout << "data " << bgcorr.data << std::endl;
//        std::cout << "data size " << bgcorr.data_size << std::endl;
//        std::cout << "data type " << bgcorr.data_type << std::endl;
//        std::cout << "dims " << bgcorr.dims << " " << bgcorr.dims[0] << " " << bgcorr.dims[1] << endl;
//        std::cout << "internal " << bgcorr.internal << std::endl;
//        std::cout << "complex " << bgcorr.isComplex << std::endl;
//        std::cout << "global " << bgcorr.isGlobal << std::endl;
//        std::cout << "logical " << bgcorr.isLogical << std::endl;
//        std::cout << "mem conserve " << bgcorr.mem_conserve << std::endl;
//        std::cout << "name " << bgcorr.name << std::endl;
//        std::cout << "nbytes " << bgcorr.nbytes << std::endl;
//        std::cout << "rank " << bgcorr.rank << std::endl;
//    }
//    std::cout << std::endl;
//
    
    //cout << "bgcorr num of fields " << Mat_VarGetNumberOfFields(&Data[DataFields::BGCORRECTIONDATA]) << endl;
    
    //matvar_t bgcorr = 
    
//    matvar_t shape;
//    shape = *Mat_VarGetStructFieldByIndex(&Data[DataFields::CALIBRATION], 8, 0);
//    
//    
//    std::cout << "class type " << shape.class_type << std::endl;
//    std::cout << "compression " << shape.compression << std::endl;
//    std::cout << "data " << shape.data << std::endl;
//    std::cout << "data size " << shape.data_size << std::endl;
//    std::cout << "data type " << shape.data_type << std::endl;
//    std::cout << "dims " << shape.dims << " " << shape.dims[0] << " " << shape.dims[1] << endl;
//    std::cout << "internal " << shape.internal << std::endl;
//    std::cout << "complex " << shape.isComplex << std::endl;
//    std::cout << "global " << shape.isGlobal << std::endl;
//    std::cout << "logical " << shape.isLogical << std::endl;
//    std::cout << "mem conserve " << shape.mem_conserve << std::endl;
//    std::cout << "name " << shape.name << std::endl;
//    std::cout << "nbytes " << shape.nbytes << std::endl;
//    std::cout << "rank " << shape.rank << std::endl;
//    std::cout << std::endl;
//    
//    cout << Mat_VarGetNumberOfFields(&shape) << endl;
//    matvar_t shapeField;
//    
//    for(int i = 0; i < Mat_VarGetNumberOfFields(&shape); i++)
//    {
//        shapeField = *Mat_VarGetStructFieldByIndex(&shape, i, 0);
//            
//        std::cout << std::endl;
//        std::cout << "class type " << shapeField.class_type << std::endl;
//        std::cout << "compression " << shapeField.compression << std::endl;
//        std::cout << "data " << shapeField.data << std::endl;
//        std::cout << "data size " << shapeField.data_size << std::endl;
//        std::cout << "data type " << shapeField.data_type << std::endl;
//        std::cout << "dims " << shapeField.dims << " " << shapeField.dims[0] << " " << shapeField.dims[1] << endl;
//        std::cout << "internal " << shapeField.internal << std::endl;
//        std::cout << "complex " << shapeField.isComplex << std::endl;
//        std::cout << "global " << shapeField.isGlobal << std::endl;
//        std::cout << "logical " << shapeField.isLogical << std::endl;
//        std::cout << "mem conserve " << shapeField.mem_conserve << std::endl;
//        std::cout << "name " << shapeField.name << std::endl;
//        std::cout << "nbytes " << shapeField.nbytes << std::endl;
//        std::cout << "rank " << shapeField.rank << std::endl;
//        std::cout << std::endl;
//    }

//    matvar_t cudo;
    
    //for(int i = 0; i < 10; i++)     // 9 is hardcoded number of fields, not expected to change
    //{
//        cudo = *Mat_VarGetCell(&namelist, 0);
        //cout << cudo << endl;

//        std::cout << "class type " << cudo.class_type << std::endl;
//        std::cout << "compression " << cudo.compression << std::endl;
//        std::cout << "data " << cudo.data << std::endl;
//        std::cout << "data size " << cudo.data_size << std::endl;
//        std::cout << "data type " << cudo.data_type << std::endl;
//        std::cout << "dims " << cudo.dims << " " << cudo.dims[0] << " " << cudo.dims[1] << endl;
//        std::cout << "internal " << cudo.internal << std::endl;
//        std::cout << "complex " << cudo.isComplex << std::endl;
//        std::cout << "global " << cudo.isGlobal << std::endl;
//        std::cout << "logical " << cudo.isLogical << std::endl;
//        std::cout << "mem conserve " << cudo.mem_conserve << std::endl;
//        //std::cout << "name " << cudo.name << std::endl;
//        std::cout << "nbytes " << cudo.nbytes << std::endl;
//        std::cout << "rank " << cudo.rank << std::endl;
//
//        //cout << *(char*)(cudo.data+4) << endl;
//        std::cout << std::endl;
    //}
    
//    matvar_t *molec = Mat_VarGetStructFieldByIndex(&Data[DataFields::MOLECULES], 1, 0);
//    cout << molec->name << endl;
    
//    mat_t *file = Mat_Open(fileName.c_str(), MAT_ACC_RDONLY);
//    
//    matvar_t *matvar;
//    
//    //TODO: throw out unnecessary fancy stuff
//    do
//    {
//        matvar = Mat_VarReadNextInfo(file);
//        if(matvar == NULL) break;
//        else VariablesInfo.push_back(*matvar);
//    }while(true);
//    
//    //for(int i = 0; i < VariablesInfo.size(); i++)
//    //{
//        matvar = Mat_VarRead(file, "data");
//        Variables.push_back(*matvar);
//    //}
//    
//    for(int i = 0; i < Variables.size(); i++)
//    {
////        matvar = Mat_VarRead(file, VariablesInfo.at(i).name);
////        Variables.push_back(*matvar);
//        
//        matvar_t temp = Variables.at(i);
//        
//        //cout << matio_classes::MAT_C_STRUCT << endl;
//        
//        if(temp.class_type == matio_classes::MAT_C_STRUCT)
//        {
//            // read the struct
////            cout << *(Mat_VarGetStructFieldnames(var2)) << endl;
////            cout << Mat_VarGetStructFieldByIndex(var2, 1, 0)->data_type << endl;
//                        
//            StructFields = Mat_VarGetStructFieldnames(&temp);
//            
//            for(int j = 0; j < temp.data_size; j++)
//            {
//                Data.push_back(*Mat_VarGetStructFieldByIndex(&temp, j, 0));
//            }
//            
//        }
//        else
//        {
//            //TODO: exception
//        }
//        
//        void *out;
//        int start = 0;
//        int stride = 1;
//        int end = 100;
//        
//        //Mat_VarReadData(mat_t *mat,matvar_t *matvar,void *data, int *start,int *stride,int *edge);
//        
//        //cout << *(Data[0]).data_type << endl;
//        cout << "read data " << Mat_VarReadData(file , &Data[0], out, &start, &stride, &end) << endl;
//        cout << out << endl;
////        cout.precision(17);
//        //cout << ((double *)out)[0] << endl;
////        
//        double hue = *(double *)(out);
////        
////        cout << hue << endl;
////        cout << hue[0] << endl;
////        for(int j = 0; j < 100; j++)
////        {
////            cout << reinterpret_cast<double>(out[j]) << endl;
////        }
//
//    }
//    
//    
//    
//    //matvar_t *var2 = Mat_VarRead(file, "data");