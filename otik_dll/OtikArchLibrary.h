#pragma once
#include <string>
#include "pch.h"

#ifdef OTIKARCHKIBRARY_EXPORTS
#define OTIKARCHKIBRARY_API __declspec(dllexport)
#else
#define OTIKARCHKIBRARY_API __declspec(dllimport)
#endif

extern "C" OTIKARCHKIBRARY_API bool MakeArch(
	const char* newArchName,
	int newArchNameLen, 
	const char* inPath,
	int inPathLen,
	const char* outPath,
	int outPathLen,
	bool use_context_independent_compression,
	bool useContextCompression);