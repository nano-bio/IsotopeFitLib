#include <stdlib.h>
#include <iostream>

#include "src/IsotopeFitter.h"

void test1() {
    std::cout << "h5readatt test 1" << std::endl;
    
    string str("tests/testfile.h5");
    H5File f = OpenH5File(str);
    
    Attribute att = f.openAttribute("NbrSamples");
    //Attribute att = new Attribute(f.openAttribute("NbrSamples"));
    
    //DataType *type = new DataType(att->getDataType());
    DataType type = att.getDataType();
    
    int a = 0; 
       
    //att->read(*type, &a);
    att.read(type, &a);
    
    std::cout << a << endl;
    
    int hue = type.getId();
    
    std::cout << hue << endl;
    
    att.close();
    f.close();
    
    //std::cout << PredType.NATIVE_INT.getClass() << endl;
}

void test2() {
    std::cout << "h5readatt test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (h5readatt) message=error message sample" << std::endl;
    
    H5File fi = OpenH5File("tests/testfile.h5");
    Attribute attr = OpenH5Attribute(fi, "NbrSamples");
    
    int fu = 0;
    
    //attr.read(attr.getDataType(), &fu);
    fu = ReadH5AttributeInt(attr);
    
    std::cout << fu << std::endl;
    
    //int hue = attr.getDataType().getId();
    
    //std::cout << hue << endl;
    
    CloseH5Attribute(attr);
    CloseH5File(fi);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% h5readatt" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (h5readatt)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (h5readatt)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (h5readatt)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (h5readatt)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

