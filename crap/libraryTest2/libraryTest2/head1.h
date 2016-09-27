#ifndef head1h
#define head1h
#include <iostream>

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C"
{
	DECLDIR int Add(int a, int b);
	DECLDIR void Func(void);
}

#endif
