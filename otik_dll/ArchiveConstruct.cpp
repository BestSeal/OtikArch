#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <filesystem>
#include "ArchiveConstruct.h"
#include "FileDispatcher.h"


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

	(*file_pointer) >> std::setw(1) >> temp;
	temp.erase();

	(*file_pointer) >> std::setw(6) >> temp;
	if (temp.compare(string(VER).append(BUILD).append(STATUS)) != 0)
		throw "The versions doesn't match";
	temp.erase();

	(*file_pointer) >> std::setw(8) >> temp;
	temp.erase(std::remove(temp.begin(), temp.end(), 0), temp.end());
	header.size = std::stoull(temp);
	temp.erase();

	(*file_pointer) >> std::setw(2) >> temp;
	temp.erase(std::remove(temp.begin(), temp.end(), 0), temp.end());
	header.file_amount = std::stoi(temp);
	temp.erase();

	(*file_pointer) >> std::setw(3) >> temp;
	temp[0] == '1' ? header.cdc = true : header.cdc = false;
	temp[1] == '1' ? header.cic = true : header.cic = false;
	temp[2] == '1' ? header.dl = true : header.dl = false;
	temp.erase();

	return header;

	(*file_pointer).seekg(position);
}

int add_file_to_archive(ofstream *file, string abs_path, string rel_path, uint16_t* file_count, bool context_compr, bool contextless_compr)
{
	uint64_t size_of_file = 0;
	if (std::filesystem::is_directory(abs_path))
	{
		for (const auto& item : std::filesystem::directory_iterator(abs_path))
		{
			size_of_file += add_file_to_archive(file, item.path().string(), rel_path, file_count, context_compr, contextless_compr);
		}
	}
	else
	{
		string file_rel_path = get_rel_path_of_file(abs_path, rel_path);

		string compressed_data = compress_string(get_file_content(abs_path), contextless_compr, context_compr, 0);
		string metadata = file_create_metadata(file_rel_path, compressed_data.size());
		(*file) << metadata;
		(*file) << compressed_data;
		size_of_file += metadata.length() + compressed_data.length();
		
		(*file_count)++;
		return size_of_file;
	}
	return size_of_file;
}

bool extract_from_archive(string arch_path_s, string extr_path_s, bool context_compr,
	bool contextless_compr, bool data_loss_protect)
{
	ifstream archive = ifstream(arch_path_s, std::ios_base::binary);
	archive_header header = read_header(&archive);
	//archive.close();
	//archive.open(arch_path_s, std::ios_base::binary);
	archive.seekg(32);
	for (int i = 0; i < header.file_amount; i++)
	{
		//get meta
		uint16_t meta_size;
		uint64_t file_size;
		string file_name;
		string file_meta;
		archive >> std::setw(16) >> file_meta;
		meta_size = std::stol(file_meta);
		archive >> std::setw(64) >> file_meta;
		file_size = std::stoull(file_meta);

		char* file_name_ch = new char[meta_size - 80];
		archive.read(file_name_ch, meta_size - 80);
		file_name = string(file_name_ch, meta_size - 80);
		//archive >> std::setw(meta_size - 80) >> file_name;

		//get content
		char* buffer = new char[file_size];
		archive.read(buffer, file_size);
		//archive >> std::setw(file_size) >> content;
		string uncomp_content = uncompress_string(string(buffer, file_size), contextless_compr, context_compr, data_loss_protect);
		
		delete[] buffer;
		delete[] file_name_ch;

		char separ = std::filesystem::path::preferred_separator;

		std::replace(file_name.begin(), file_name.end(), '/', separ);
		string abs_path_s = string(extr_path_s).append(1, separ).append(file_name);
		std::filesystem::path abs_path = std::filesystem::path(abs_path_s);

		std::filesystem::create_directories(abs_path.parent_path());
		ofstream output_file = ofstream(abs_path_s, std::ios_base::binary);
		output_file << uncomp_content;
	}
	return true;
}
