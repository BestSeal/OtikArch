#include "pch.h"
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include "ArchiveConstruct.h"

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

#define VER "00" //current version
#define BUILD "01" //current build
/**
* current status
* valid statuses:
* _A: alpha build
* _B: beta build
* _R: release build
*/
#define STATUS "_A"

#define CONTEXTUAL_DEPENDENT_COMPRESSION 0
#define CONTEXTUAL_INDEPENDENT_COMPRESSION 0
#define DATA_LOSS_PROTECTION 0

/**
*@param size: size of the result file
*@param cdc: contextual dependent compression 
*@param cic: contextual independent compression
*@param dlp: data loss protection
* @brief header; size: 32 bytes
*/
void fill_header(ofstream *file_pointer, uint64_t size, uint16_t files_amount, bool cdc, bool cic, bool dlp)
{
	std::streampos position = (*file_pointer).tellp();
	(*file_pointer).flush();
	(*file_pointer).seekp(std::ios_base::beg);

	(*file_pointer).fill(0);

	(*file_pointer) << std::setw(7) << "OTIK5SG";
	(*file_pointer).put(0);

	(*file_pointer) << std::setw(2) << VER;
	(*file_pointer) << std::setw(2) << BUILD;
	(*file_pointer) << std::setw(2) << STATUS;
	(*file_pointer) << std::setw(8) << 0;
	(*file_pointer) << std::setw(2) << files_amount;
	(*file_pointer) << std::setw(1) << cdc;
	(*file_pointer) << std::setw(1) << cic;
	(*file_pointer) << std::setw(1) << dlp;
	(*file_pointer) << std::setw(5) << ""; //reserve

	(*file_pointer).seekp(position);
	return;
}

void add_file_to_the_archive(string filepath_s, ofstream *archive_pointer)
{

}
