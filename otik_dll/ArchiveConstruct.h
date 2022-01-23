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
	uint32_t file_amount;
	bool cdc;
	bool cic;
	bool dl;
};

void fill_header(ofstream* file_pointer, uint64_t size, uint16_t files_amount, bool cdc, bool cic, bool dlp);
int add_file_to_archive(ofstream* file, string abs_path, string rel_path, uint16_t* file_count, bool context_compr, bool contextless_compr);
bool extract_from_archive(string arch_path_s, string extr_path_s, bool context_compr,
	bool contextless_compr, bool data_loss_protect);
