#pragma once
#include <string>
#include "pch.h"

#ifdef OTIKARCHKIBRARY_EXPORTS
#define OTIKARCHKIBRARY_API __declspec(dllexport)
#else
#define OTIKARCHKIBRARY_API __declspec(dllimport)
#endif

extern "C" OTIKARCHKIBRARY_API bool MakeArch(
	const char* new_arch_name,
	int new_arch_name_len,
	const char* in_path, 
	int in_path_len, 
	const char* out_path, 
	int out_pathLen,
	bool use_context_independent_compression, 
	bool use_context_compression);

extern "C" OTIKARCHKIBRARY_API bool ExtractFrom(
	const char* arch_path, 
	int arch_path_len, 
	const char* extr_path, 
	int extr_path_len,
	bool use_context_independent_compression, 
	bool use_context_compression);
