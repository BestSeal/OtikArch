#pragma once
#include <string>
#include "pch.h"

#ifdef OTIKARCHKIBRARY_EXPORTS
#define OTIKARCHKIBRARY_API __declspec(dllexport)
#else
#define OTIKARCHKIBRARY_API __declspec(dllimport)
#endif

extern "C" OTIKARCHKIBRARY_API bool MakeArch(char* new_arch_name, 
	int new_arch_name_len,
	char* in_path, 
	int in_path_len, 
	char* out_path, 
	int out_pathLen,
	bool use_context_independent_compression,
	bool use_context_compression);