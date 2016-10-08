#ifndef MATBINFUNC_H
#define MATBINFUNC_H

/* System headers */
//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

/* External headers */

/* Namespaces */
using namespace std;

/* Place for storing contents of data tags and starting indexes of data blocks */
extern vector<int> DataBlocks;

extern bool endianIndicator;

//extern struct DataBlock
//{
//    int dataType;
//    
//};

enum miDataType
{
    miINT8 = 1,
    miUINT8,
    miINT16,
    miUINT16,
    miINT32,
    miUINT32,
    miSINGLE,
    miDOUBLE = 9,
    miINT64 = 12,
    miUINT64,
    miMATRIX,
    miCOMPRESSED,
    miUTF8,
    miUTF16,
    miUTF32
};
                
enum mxArrayClasses
{
    mxCELL = 1,
    mxSTRUCT,
    mxOBJECT,
    mxCHAR,
    mxSPARSE,
    mxDOUBLE,
    mxSINGLE,
    mxINT8,
    mxUINT8,
    mxINT16,
    mxUINT16,
    mxINT32,
    mxUINT32,
    mxINT64,
    mxUINT64
};

fstream OpenMatBinFile(string fileName);
void ReadMatBinFile(fstream &File, unsigned char *&outBuffer, int &outSize);
bool CheckEndianIndicator(unsigned char *inBuffer);
void Read8ByteDataTag(unsigned char *inBuffer, int startIndex, int &outDataType, int &outNumOfBytes);
void ReadDataBlock(unsigned char *inBuffer, int startIndex, int dataType, int numOfBytes); //TODO: kam vystup
void ProcessFileStructure(unsigned char *inBuffer, int size);
void UncompressMatBinData(unsigned char *inCompData, int inCompBytes, unsigned char *&outUncompData, int &outUncompCount);
void CloseMatBinFile(fstream &File);

/* Definitions of inline utility functions */
/* Joins two bytes/chars, big-endian */
inline uint16_t PackBytesToUint16BE(unsigned char *Array, int startIndex)
{
    uint16_t retval = (Array[startIndex] << 8 | Array[startIndex + 1]);
    return retval;
}

/* Joins four bytes/chars, big-endian */
inline uint32_t PackBytesToUint32BE(unsigned char *Array, int startIndex)
{
    uint32_t retval = (Array[startIndex] << 24 | Array[startIndex + 1] << 16 | Array[startIndex + 2] << 8 | Array[startIndex + 3]);
    return retval;
}

/* Joins two bytes/chars, little-endian */
inline uint16_t PackBytesToUint16LE(unsigned char *Array, int startIndex)
{
    uint16_t retval = (Array[startIndex + 1] << 8 | Array[startIndex]);
    return retval;
}

/* Joins four bytes/chars, little-endian */
inline uint32_t PackBytesToUint32LE(unsigned char *Array, int startIndex)
{
    uint32_t retval = (Array[startIndex + 3] << 24 | Array[startIndex + 2] << 16 | Array[startIndex + 1] << 8 | Array[startIndex]);
    return retval;
}

/* Joins eight bytes into double, endian invariant */
inline double PackBytesToDouble(unsigned char *Array, int startIndex)
{
    unsigned char *arr = new unsigned char[8];
    
    for(int i = 0; i < 8; i++)
    {
        arr[i] = Array[i + startIndex];
    }
    
    double retval;
    memcpy(&retval, arr, sizeof(retval));
    std::cout << "retval " << retval << std::endl;
    return retval;
}

#endif /* MATBINFUNC_H */

