#include "IsotopeFitter.h"
//#include <matio.h>
//#include <stdint.h>


//string inputFile("../testfile.h5");

int main(int argc, char** argv)
{    
//    vector<double> *frgd = new vector<double>();
//    //vector<double> gg = *frgd;
//    
//    frgd->push_back(4);
//    
//    cout << frgd->at(0) << endl;
//    
//    delete frgd;
    
    //cout << argv[1] << endl;

    //for (int i=0; i<10; i++)
    //{
        //cout << "pass " << i << endl;
        //getchar();
        string str = "/home/matlab/Michal/dev/IsotopeFitter/tests/testfileifd.ifd";
        LoadIFDFile(str);
        //cout << "pass " << i << " done" << endl;
        //getchar();
        
        cout << IFData::endInd << endl;
        cout << "done" << endl;
    //}
    
    return 0;
}