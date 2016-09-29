/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>

#define DLL_EXPORT
#include "DLLTest.h"

extern "C"
{
    DECLDIR int Add(int a, int b)
    {
        return(a+b);
    }
    
    DECLDIR void Function(void)
    {
        std::cout << "works\n";
    }
}