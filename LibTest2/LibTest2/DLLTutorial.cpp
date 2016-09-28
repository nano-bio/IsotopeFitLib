#include <iostream>

#define DLL_EXPORT
#include "DLLTutorial.h"

extern "C"
{
	DECLDIR int Add(int a, int b)
	{
		return(a + b);
	}

	DECLDIR void Function(void)
	{
		std::cout << "DLL Called! nazdar\n";
	}
}
