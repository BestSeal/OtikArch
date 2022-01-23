#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include "ArchiveConstruct.h"

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
	(*file_pointer) << std::setw(8) << size;
	(*file_pointer) << std::setw(2) << files_amount;
	(*file_pointer) << std::setw(1) << cdc;
	(*file_pointer) << std::setw(1) << cic;
	(*file_pointer) << std::setw(1) << dlp;
	(*file_pointer) << std::setw(5) << ""; //reserve

	(*file_pointer).seekp(position);
	return;
}

archive_header read_header(ifstream* file_pointer)
{
	archive_header header;
	std::streampos position = (*file_pointer).tellg();

	string temp;
	(*file_pointer) >> std::setw(7) >> temp;
	if (temp.compare("OTIK5SG") != 0)
		throw "The format is not supported";
	temp.clear();

	(*file_pointer) >> std::setw(6) >> temp;
	if (temp.compare(string(VER).append(BUILD).append(STATUS)) != 0)
		throw "The versions doesn't match";
	temp.clear();

	(*file_pointer) >> std::setw(8) >> temp;
	temp.erase(std::remove(temp.begin(), temp.end(), 0), temp.end());
	header.size = std::stoull(temp);
	temp.clear();

	(*file_pointer) >> std::setw(2) >> temp;
	temp.erase(std::remove(temp.begin(), temp.end(), 0), temp.end());
	header.files_amount = std::stoi(temp);
	temp.clear();

	(*file_pointer) >> std::setw(3) >> temp;
	temp[0] == '1' ? header.cdc = true : header.cdc = false;
	temp[1] == '1' ? header.cic = true : header.cic = false;
	temp[2] == '1' ? header.dl = true : header.dl = false;
	temp.clear();

	return header;

	(*file_pointer).seekg(position);
}
