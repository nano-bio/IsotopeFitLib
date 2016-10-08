#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <array>
//#include <utility>
#include <stdint.h>
#include <string.h>

#include "src/IsotopeFitter.h"

#include <zlib.h>

using namespace std;

void test1() {
    std::cout << "MatBin open close" << std::endl;
    
    fstream fs = OpenMatBinFile("tests/testfileifd.ifd");
    std::cout << fs.is_open() << std::endl;
    CloseMatBinFile(fs);
    
    //std::cout << &fs << std::endl;
    //std::cout << (*&fs).gcount() << std::endl;
    
    if(fs.is_open())
    {
        fs.close();
        std::cout << "bol stale otvoreny" << std::endl;
    }
    else
    {
        std::cout << "zavrel ho" << std::endl;
    }

}

void test2() {
    std::cout << "MatBin open read close native" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (MatBin) message=error message sample" << std::endl;
    
//    std::ofstream out("out.txt");
//    std::streambuf *coutbuf = std::cout.rdbuf();
//    std::cout.rdbuf(out.rdbuf());
    
    fstream fs = OpenMatBinFile("tests/testfileifd.ifd");

    char* hue;
    
    streampos size = fs.tellg();
    hue = new char[size];
    fs.seekg(0, ios::beg);
    fs.read(hue, size);
    
    std::cout << "num of bytes " << size << std::endl;
    
    //std::cout << hue[] << std::endl;

    //std::cout <<  << std::endl;
    
    std::cout << "128 byte header" << std::endl;
    for (int i=0; i<128; i++)
    {
        std::cout << hue[i];
    }
    
    std::cout << std::endl;
    
    int32_t combo = (hue[116]<<24 | hue[117]<<16 | hue[118]<<8 | hue[119]);
    std::cout << "subsys data offset " << combo << std::endl;
    
    int32_t combo2 = (hue[120]<<24 | hue[121]<<16 | hue[122]<<8 | hue[123]);
    std::cout << "subsys data offset " << combo2 << std::endl;
    
    //int64_t combo12 = (combo2<<32 | combo);
    //std::cout << combo12 << std::endl;
    
    uint16_t combo3 = (hue[125] << 8 | hue[124]);
    std::cout << "version " << combo3 << std::endl;
    
    int32_t combo4 = (hue[131]<<24 | hue[130]<<16 | hue[129]<<8 | hue[128]);
    std::cout << "data type " << combo4 << std::endl;
    
    int32_t combo5 = (hue[135]<<24 | hue[134]<<16 | hue[133]<<8 | hue[132]);
    std::cout << "num of bytes " <<combo5 << std::endl;
    
    char * compressedData = new char[combo5];
    
    for(int i=0; i<combo5; i++)
    {
        compressedData[i]=hue[i+136];
    }
    
    Bytef *uncompressed = new Bytef[10*combo5];
    uLongf compressedLength = static_cast<uLongf>(combo5);
    unsigned char * compressedData2 = reinterpret_cast<Bytef*>(compressedData);
    uLongf uncompressedLength = 10*combo5;
    
    std::cout << "uncompressed length before " << uncompressedLength << std::endl;

    
    std::cout << "compressed data " << static_cast<short>(compressedData2[0]) << std::endl;
    std::cout << "hue " <<static_cast<short>(hue[136]) << std::endl;
    std::cout << "compressed data " << static_cast<short>(compressedData[0]) << std::endl;
    
    int res = uncompress(uncompressed, &uncompressedLength, compressedData2, compressedLength);
    std::cout << "decompress result " << res << std::endl;
    
    //std::cout << static_cast<short>(uncompressed[0]) << std::endl;
    std::cout << "uncompressed length after " << uncompressedLength << std::endl;

    for(int i=0; i<300; i++)
    {
        std::cout << i << "\t" << uncompressed[i] << "\t" << static_cast<short>(uncompressed[i]) << std::endl;
    }
    
    int32_t combo6 = (uncompressed[3]<<24 | uncompressed[2]<<16 | uncompressed[1]<<8 | uncompressed[0]);
    std::cout << "unc data type " << combo6 << std::endl;

//    int32_t combo7 = (uncompressed[7]<<24 | uncompressed[6]<<16 | uncompressed[5]<<8 | uncompressed[4]);
//    std::cout << "unc num of bytes " << combo7 << std::endl;
    
    int32_t nazdar = PackBytesToUint32LE(uncompressed, 4);
    std::cout << "unc num of bytes " << nazdar << std::endl;

    int32_t bazdar = PackBytesToUint32LE(uncompressed, 8);
    std::cout << "unc data type " << bazdar << std::endl;
    
    int32_t fazdar = PackBytesToUint32LE(uncompressed, 12);
    std::cout << "unc cudo " << fazdar << std::endl;
    
    std::cout << "unc flags " << static_cast<short>(uncompressed[18]) << std::endl;

    std::cout << "unc class " << static_cast<short>(uncompressed[19]) << std::endl;
    
    int32_t gazdar = PackBytesToUint32LE(uncompressed, 24);
    std::cout << "unc data type arr dim " << gazdar << std::endl;
    
    int32_t razdar = PackBytesToUint32LE(uncompressed, 28);
    std::cout << "unc arr dim " << razdar << std::endl;
    
    int32_t hazdar = PackBytesToUint32LE(uncompressed, 32);
    std::cout << "unc arr dim2 " << hazdar << std::endl;
    
    int32_t zazdar = PackBytesToUint32LE(uncompressed, 36);
    std::cout << "unc arr dim3 " << zazdar << std::endl;
    
    int32_t qqq = PackBytesToUint32LE(uncompressed, 40);
    std::cout << "unc data type arr name " << qqq << std::endl;
    
    int32_t www = PackBytesToUint32LE(uncompressed, 44);
    std::cout << "unc cudo arr name " << www << std::endl;
    
    for(int i=48; i<56; i++)
    {
        std::cout << static_cast<short>(uncompressed[i]);
    }
    std::cout << std::endl;
    
    int32_t eee = PackBytesToUint32LE(uncompressed, 56);
    std::cout << "unc data type " << eee << std::endl;
    
    int32_t rrr = PackBytesToUint32LE(uncompressed, 60);
    std::cout << "unc num bytes " << rrr << std::endl;

    for(int i=64; i<200; i++)
    {
        std::cout << uncompressed[i];
    }
    std::cout << std::endl;

    int32_t ttt = PackBytesToUint32LE(uncompressed, 200);
    std::cout << "unc data type " << ttt << std::endl;
    
    int32_t yyy = PackBytesToUint32LE(uncompressed, 204);
    std::cout << "unc num bytes " << yyy << std::endl;    
    
    int32_t uuu = PackBytesToUint32LE(uncompressed, 208);
    std::cout << "unc data type " << uuu << std::endl;
    
    int32_t iii = PackBytesToUint32LE(uncompressed, 212);
    std::cout << "unc num bytes " << iii << std::endl;
    
    std::cout << "unc flags " << static_cast<short>(uncompressed[218]) << std::endl;

    std::cout << "unc class " << static_cast<short>(uncompressed[219]) << std::endl;

    
    int32_t ooo = PackBytesToUint32LE(uncompressed, 224);
    std::cout << "unc again matrix datatype " << ooo << std::endl;
    
    int32_t ppp = PackBytesToUint32LE(uncompressed, 228);
    std::cout << "unc again matrix cudo " << ppp << std::endl;
    
    int32_t aaa = PackBytesToUint32LE(uncompressed, 232);
    std::cout << "unc again matrix dim1 " << aaa << std::endl;
    int32_t sss = PackBytesToUint32LE(uncompressed, 236);
    std::cout << "unc again matrix dim2 " << sss << std::endl;
    
    int32_t ddd = PackBytesToUint32LE(uncompressed, 240);
    std::cout << "unc data type arr name " << ddd << std::endl;
    
    int32_t q1 = PackBytesToUint32LE(uncompressed, 244);
    std::cout << "unc cudo arr name " << q1 << std::endl;
    
//    for(int i=248; i< 257; i++)
//    {
//        std::cout << uncompressed[i];
//    }
//    std::cout << std::endl;

    int32_t w1 = PackBytesToUint32LE(uncompressed, 248);
    std::cout << "unc data datatype " << w1 << std::endl;
    
    int32_t w2 = PackBytesToUint32LE(uncompressed, 252);
    std::cout << "unc data cudo " << w2 << std::endl;
    
    unsigned char *asdf = new unsigned char[8];
    unsigned char *asdf2 = new unsigned char[8];

    
    for(int i=0; i< 8; i++)
    {
        asdf[i] = uncompressed[i+256];
        std::cout << static_cast<short>(asdf[i]) << std::endl;
    }
    
    double combo8;
    memcpy(&combo8, asdf, sizeof(combo8));
    std::cout << "combo8 " << combo8 << std::endl;
    
    std::cout << PackBytesToDouble(uncompressed, 256) << std::endl;
   

//    std::cout.rdbuf(coutbuf);
    
    CloseMatBinFile(fs);
}

void test3() {
    std::cout << "MatBin open read close lib" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (MatBin) message=error message sample" << std::endl;
    
    fstream file = OpenMatBinFile("tests/testfileifd.ifd");
    
//    char *hue = new char[5];
//    cout << hue[0] << endl;
    
    unsigned char *contents;
    int contentsSize;
    ReadMatBinFile(file, contents, contentsSize);
    
    CloseMatBinFile(file);
    
    cout << contentsSize << endl;
    cout << contents[0] << endl;
    
    endianIndicator = CheckEndianIndicator(contents);
    cout << endianIndicator << endl;
        
    int dt;
    int count;
    Read8ByteDataTag(contents, 128, dt, count);
    cout << dt << " " << count << endl;
    
    ProcessFileStructure(contents, contentsSize);
    
    for(int i=0; i<DataBlocks.size(); i++)
    {
        cout << DataBlocks.at(i) << endl;
    }
    
    unsigned char *contentsSub = new unsigned char[DataBlocks.at(1)];
    
    for(int i=0; i<DataBlocks.at(1); i++)
    {
        contentsSub[i] = contents[i + DataBlocks.at(2)];
    }
    cout << DataBlocks.at(2) << endl;
    cout << static_cast<short>(contentsSub[0]) << endl;
    
    unsigned char *outUncompData;
    int outUncompCount;
    UncompressMatBinData(contentsSub, DataBlocks.at(1), outUncompData, outUncompCount);
    cout << static_cast<short>(outUncompData[0]) << " " << outUncompCount << endl;

    ProcessFileStructure(outUncompData, outUncompCount);
    
    for(int i=0; i<DataBlocks.size(); i++)
    {
        cout << DataBlocks.at(i) << endl;
    }
    
//    unsigned char asdf[] = {131, 102, 242, 206, 220, 105, 161, 63};
//    
//    double combo8;
//    memcpy(&combo8, &asdf, sizeof(combo8));
//    std::cout << combo8 << std::endl;
}

void test4() {
    std::cout << "MatBin load entire file" << std::endl;
    
    fstream file = OpenMatBinFile("tests/testfileifd.ifd");
    
    unsigned char *contents;
    int contentsSize;
    ReadMatBinFile(file, contents, contentsSize);
    
    CloseMatBinFile(file);
    
    endianIndicator = CheckEndianIndicator(contents);
    
    bool stop = false;
    int ctr = 0;
    

    ProcessFileStructure(contents, contentsSize);

    do
    {
        for(int i=0; i<DataBlocks.size(); i = i + 3)
        {
            switch(DataBlocks.at(i))
            {
                case miDataType::miCOMPRESSED :
                {
                    cout << "found compressed" << endl;

                    unsigned char *contentsSub = new unsigned char[DataBlocks.at(1)];

                    for(int i=0; i<DataBlocks.at(1); i++)
                    {
                        contentsSub[i] = contents[i + DataBlocks.at(2)];
                    }
                    cout << DataBlocks.at(2) << endl;
                    cout << static_cast<short>(contentsSub[0]) << endl;

                    unsigned char *outUncompData;
                    int outUncompCount;
                    UncompressMatBinData(contentsSub, DataBlocks.at(1), outUncompData, outUncompCount);
                    cout << static_cast<short>(outUncompData[0]) << " " << outUncompCount << endl;

                    DataBlocks.clear();

                    ProcessFileStructure(outUncompData, outUncompCount);
                    break;
                }
                case miDataType::miMATRIX :
                {
                    cout << "found matrix" << endl;
                    
                    //TODO: routine for reading matrices
                    
                    stop = true;
                    break;
                }
                default : break; //TODO: not implemented
            }
        }
    }while(!stop);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% MatBin" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

//    std::cout << "%TEST_STARTED% test1 (MatBin)" << std::endl;
//    test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (MatBin)" << std::endl;

//    std::cout << "%TEST_STARTED% test2 (MatBin)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (MatBin)" << std::endl;
    
//    std::cout << "%TEST_STARTED% test3 (MatBin)\n" << std::endl;
//    test3();
//    std::cout << "%TEST_FINISHED% time=0 test3 (MatBin)" << std::endl;
    
    std::cout << "%TEST_STARTED% test4 (MatBin)\n" << std::endl;
    test4();
    std::cout << "%TEST_FINISHED% time=0 test4 (MatBin)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

