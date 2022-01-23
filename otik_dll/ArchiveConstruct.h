#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

void fill_header(std::ofstream* file_pointer, uint64_t size, uint16_t files_amount, bool cdc, bool cic, bool dlp);
void add_file_to_the_archive(std::string filepath_s, std::ofstream* archive_pointer);
