#pragma once
#include <string>

#ifdef OTIKARCHKIBRARY_EXPORTS
#define OTIKARCHKIBRARY_API __declspec(dllexport)
#else
#define OTIKARCHKIBRARY_API __declspec(dllimport)
#endif

extern "C" OTIKARCHKIBRARY_API bool MakeArch(char* newArchName, 
	int newArchNameLen, 
	char* inPath,
	int inPathLen,
	char* outPath,
	int outPathLen,
	bool useCompression, 
	bool useArithmeticCompression, 
	bool useContextCompression);