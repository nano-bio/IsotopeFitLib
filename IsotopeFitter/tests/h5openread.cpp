#include <stdlib.h>
#include <iostream>

#include "src/IsotopeFitter.h"

void test1() {
    std::cout << "h5test test 1" << std::endl;
    
    string str("tests/testfile.h5");
    
    cout << str << "\n";
    
    cout << IsH5File(str) << "\n";    
    
    H5File f = OpenH5File(str);
    
    DataSet ds = f.openDataSet("/FullSpectra/MassAxis");
    DataSpace dsp = ds.getSpace();
    
    string bue = StrType(ds).fromClass();
    
    cout << bue << endl;
    
    float data[100000] = {};
    
    try
    {
        ds.read(data, PredType::NATIVE_FLOAT);
    }
    catch(Exception e)
    {
        e.printError();
    }
    
    dsp.close();
    ds.close();
    f.close();
    
    for(int i=1000; i<1010;i++)
    {
        cout << data[i] << "\n";
    }
}

void test2() {
    std::cout << "h5test test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
    
    H5File fi = OpenH5File("tests/testfile.h5");
    DataSet dase = OpenH5DataSet(fi, "/FullSpectra/MassAxis");
    
    float da[99750];
    
    ReadH5DataSet(dase, da);
    
    for(int i=1000; i<1010;i++)
    {
        cout << da[i] << "\n";
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% h5test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (h5test)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (h5test)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (h5test)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (h5test)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

