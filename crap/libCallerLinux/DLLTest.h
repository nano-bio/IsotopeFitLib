/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLLTest.h
 * Author: matlab
 *
 * Created on September 28, 2016, 8:55 AM
 */

#ifndef DLLTEST_H
#define DLLTEST_H
#include <iostream>

#if defined _WIN32
    #if defined DLL_EXPORT
    #define DECLDIR __declspec(dllexport)
    #else
    #define DECLDIR __declspec(dllimport)
    #endif
#else
#define DECLDIR
#endif

extern "C"
{
    DECLDIR int Add(int a, int b);
    DECLDIR void Function(void);
}

#endif /* DLLTEST_H */

