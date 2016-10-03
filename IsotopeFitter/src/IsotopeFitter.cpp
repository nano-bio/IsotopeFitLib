#include "IsotopeFitter.h"
#include <stdint.h>

string inputFile("../testfile.h5");

int main(int argc, char** argv)
{    

    return 0;
}

//TODO: tidy up
/* Utility functions, will be moved */
/* Joins two bytes/chars, big-endian */
//inline uint16_t PackBytesToUint16BE(unsigned char *Array, int startIndex)
//{
//    uint16_t retval = (Array[startIndex] << 8 | Array[startIndex + 1]);
//    return retval;
//}
//
///* Joins four bytes/chars, big-endian */
//inline uint32_t PackBytesToUint32BE(unsigned char *Array, int startIndex)
//{
//    uint32_t retval = (Array[startIndex] << 24 | Array[startIndex + 1] << 16 | Array[startIndex + 2] << 8 | Array[startIndex + 3]);
//    return retval;
//}
//
///* Joins two bytes/chars, little-endian */
//inline uint16_t PackBytesToUint16LE(unsigned char *Array, int startIndex)
//{
//    uint16_t retval = (Array[startIndex + 1] << 8 | Array[startIndex]);
//    return retval;
//}
//
///* Joins four bytes/chars, little-endian */
//inline uint32_t PackBytesToUint32LE(unsigned char *Array, int startIndex)
//{
//    uint32_t retval = (Array[startIndex + 3] << 24 | Array[startIndex + 2] << 16 | Array[startIndex + 1] << 8 | Array[startIndex]);
//    return retval;
//}