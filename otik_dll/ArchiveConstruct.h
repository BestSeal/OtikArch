#pragma once

#include "pch.h"
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

typedef struct archive_header {
	uint64_t size;
	uint16_t files_amount;
	bool cdc;
	bool cic;
	bool dl;
};

void fill_header(ofstream* file_pointer, uint64_t size, uint16_t files_amount, bool cdc, bool cic, bool dlp);
