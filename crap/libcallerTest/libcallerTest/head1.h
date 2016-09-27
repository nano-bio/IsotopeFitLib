#ifndef head1h
#define head1h
#include <iostream>

//#if defined DLL_EXPORT
//#define DECLDIR __declspec(dllexport)
//#else
//#define DECLDIR __declspec(dllimport)
//#endif

extern "C"
{
	__declspec(dllexport) int Add(int a, int b);
	__declspec(dllexport) void Func(void);
}

#endif
