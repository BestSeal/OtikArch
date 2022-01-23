#include "pch.h"
#include "OtikArchLibrary.h"
#include "ArchiveConstruct.h"
#include "StringDispatcher.h"
#include "FileDispatcher.h"
#include <fstream>
#include <string>
#include <vector>
#include <clocale>

using std::ofstream;
using std::string;
using std::vector;

#ifdef _DEBUG
#include <iostream>
using std::vector;
using std::ifstream;

int main(int argc, char* argv[])
{
	vector<ifstream> vffiles = vector<ifstream>(argc);
	for (int i = 0; i < argc; i++)
	{
		vffiles[i] = ifstream(argv[i], std::ios::binary);
	}
	int attempts = 0;

	ofstream res_archive;
	string archive_name = "new_archive.otik5";
	while (std::filesystem::exists(archive_name))
	{
		attempts++;
		archive_name.clear();
		archive_name.append("new_archive (").append(std::to_string(attempts)).append(").otik5");
	}
	res_archive = ofstream(archive_name, std::ios_base::binary);

	//std::cout << file_create_metadata("D:\\University\\critical path.png", 46) << std::endl;
	//MakeArch("file.arch", 10, "\"D:\\Ivan\\Разное\\anekdotix-117727.jpg\"\"D:\\Ivan\\Разное\\Memes\"", 60, "D:\\Ivan", 8, false, false);
	ExtractFrom("D:\\Ivan\\file.arch", 17, "D:\\Ivan\\new", 11, 0, 0);
	res_archive.close();
}
#endif // DEBUG


/**
* @param newArchName				target file name
* @param newArchNameLen				length of the name of file
* @param inPath						paths to the end files to archive
* @param outPath					where to save the end file
*/
bool MakeArch(const char* new_arch_name, int new_arch_name_len, 
	const char* in_path, int in_path_len, const char* out_path, int out_pathLen,
	bool use_context_independent_compression, bool use_context_compression)
{
	setlocale(LC_ALL, "");
	string arch_name = string(new_arch_name, new_arch_name_len);
	string arch_path = string(out_path).append(1, std::filesystem::path::preferred_separator).append(arch_name);
	ofstream new_arch(arch_path, std::ios::binary);

	vector<string> file_names = dispatch_filenames(in_path, in_path_len);
	string rel_path = get_rel_path_of_files(file_names);
	fill_header(&new_arch, 0, 0, use_context_compression, use_context_independent_compression, 0);
	
	uint64_t summary_size = 32;
	new_arch.seekp(32);

	uint16_t file_amount = 0;
	for (int i = 0; i < file_names.size(); i++)
	{
		summary_size += add_file_to_archive(&new_arch, file_names[i], rel_path, &file_amount, use_context_compression,
			use_context_independent_compression);
	}

	fill_header(&new_arch, summary_size, file_amount, use_context_compression, use_context_independent_compression, 0);
	return true;
}

bool ExtractFrom(const char* arch_path, int arch_path_len, const char* extr_path, int extr_path_len,
	bool use_context_independent_compression, bool use_context_compression)
{
	setlocale(LC_ALL, "");
	string arch_path_s = string(arch_path, arch_path_len);
	string extr_path_s = string(extr_path, extr_path_len);
	return extract_from_archive(arch_path_s, extr_path_s, use_context_independent_compression, use_context_compression, 0);
}
