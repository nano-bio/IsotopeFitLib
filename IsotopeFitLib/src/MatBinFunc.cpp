/* Header for this sublibrary, takes care of all includes and namespace declarations */
#include "../include/MatBinFunc.h"

/* Function implementations*/

fstream OpenMatBinFile(string fileName)
{
    fstream fstr(fileName, ios::in | ios::out | ios::binary | ios::ate);
    return fstr;
}

void ReadMatBinFile(fstream &File, char* outBuffer)
{
    streampos size = File.tellg();
    outBuffer = new char[size];
    File.seekg(0, ios::beg);
    File.read(outBuffer, size);
}

void CloseMatBinFile(fstream &File)
{
    File.close();
}