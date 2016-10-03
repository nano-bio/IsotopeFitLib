#ifndef ISOTOPEFITTER_H
#define ISOTOPEFITTER_H

#include <cstdlib>
#include <iostream>

#include "../../IsotopeFitLib/include/IsotopeFitLib.h"

//#include <hdf5.h>
//#include <H5Cpp.h>
//#include <H5File.h>

//#include <H5PacketTable.h>

using namespace std;
//using namespace H5;

//TODO: tidy up
/* Temporarily declared here */
//inline uint16_t PackBytesToUint16BE(unsigned char *Array, int startIndex);
//inline uint32_t PackBytesToUint32BE(unsigned char *Array, int startIndex);
//inline uint16_t PackBytesToUint16LE(unsigned char *Array, int startIndex);
//inline uint32_t PackBytesToUint32LE(unsigned char *Array, int startIndex);

/* Utility functions, will be moved */
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

#endif /* ISOTOPEFITTER_H */

