/* This source file contains functions for working with Matlab binary format. */

/* Header for this sublibrary, takes care of all includes and namespace declarations */
#include "../include/MatBinFunc.h"
#include <zlib.h>

#include <vector>

using namespace std;

vector<int> DataBlocks;
bool endianIndicator;

/* Constants declarations */
const uint8_t ENDIAN_INDICATOR_INDEX = 126;
const uint8_t FIRST_INDEX_AFTER_HEADER = 128;

/* Function implementations*/
/* Opens Matlab binary file and returns handle */
fstream OpenMatBinFile(string fileName)     //TODO: do read and write access separately
{
    fstream fstr(fileName, ios::in | ios::out | ios::binary | ios::ate);
    return fstr;
}

/* Reads entire Matlab binary file into specified buffer */
void ReadMatBinFile(fstream &File, unsigned char *&outBuffer, int &outSize)
{
    streampos size = File.tellg();
    char *outBuf = new char[size];
    File.seekg(0, ios::beg);
    File.read(outBuf, size);
    outSize = size;
    outBuffer = reinterpret_cast<unsigned char*>(outBuf);
}

/* Parses header of a previously read Matlab binary file. Returns 1 if endian flag is big and 0 when little */
bool CheckEndianIndicator(unsigned char *inBuffer)
{
    if(inBuffer[ENDIAN_INDICATOR_INDEX] == 'M')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Read8ByteDataTag(unsigned char *inBuffer, int startIndex, int &outDataType, int &outNumOfBytes)
{
    if(endianIndicator)
    {
        outDataType = PackBytesToUint32BE(reinterpret_cast<unsigned char*>(inBuffer), startIndex);
        outNumOfBytes = PackBytesToUint32BE(reinterpret_cast<unsigned char*>(inBuffer), startIndex + 4);
    }
    else
    {
        outDataType = PackBytesToUint32LE(reinterpret_cast<unsigned char*>(inBuffer), startIndex);
        outNumOfBytes = PackBytesToUint32LE(reinterpret_cast<unsigned char*>(inBuffer), startIndex + 4);
    }
            
//    switch(dt)
//    {
//        case DataType::miCOMPRESSED :
//        {
//            outDataType = DataType::miCOMPRESSED;
//            //DataBlocks.push_back(DataType::miCOMPRESSED);
//            break;
//        }
//        case DataType::miINT32 :
//        {
//            outDataType = DataType::miINT32;
//            break;
//        }
//        default : break; //TODO: throw NotImplementedException
//    }
        
    //DataBlocks.push_back(outNumOfBytes);
    
    //DataBlocks.push_back(startIndex + 8);
}

void ReadDataBlock(unsigned char *inBuffer, int startIndex, int dataType, int numOfBytes, unsigned char *&outBuffer) //TODO: output where?
{
    
}

void ProcessFileStructure(unsigned char *inBuffer, int size)
{
    int counter = 0;
    int offset = 0;
    
    int dataType;
    int numOfBytes;
    
    // cutting out header
    if(inBuffer[0] == 'M')
    {
        offset = FIRST_INDEX_AFTER_HEADER;
    }
    
    do
    {
        Read8ByteDataTag(inBuffer, offset + counter, dataType, numOfBytes);
        DataBlocks.push_back(dataType);
        DataBlocks.push_back(numOfBytes);
        DataBlocks.push_back(offset + 8 + counter);
        
        counter += 8 + numOfBytes;
    }while(offset + counter < size);
}

void UncompressMatBinData(unsigned char *inCompData, int inCompBytes, unsigned char *&outUncompData, int &outUncompCount)
{    
    outUncompData = new unsigned char[inCompBytes * 10];
    uLongf inBytesCount = static_cast<uLongf>(inCompBytes);
    uLongf outBytesCount = inCompBytes * 10;
    
    int res = uncompress(outUncompData, &outBytesCount, inCompData, inBytesCount);  //TODO: error handling
    std::cout << "decompress result " << res << std::endl;
    
    outUncompCount = outBytesCount;
}

/* Closes access to Matlab binary file */
void CloseMatBinFile(fstream &File)
{
    File.close();
}

