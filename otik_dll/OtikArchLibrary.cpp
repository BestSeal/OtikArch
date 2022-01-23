#include "pch.h"
#include "OtikArchLibrary.h"
#include "ArchiveConstruct.h"
#include "StringDispatcher.h"
#include "FileDispatcher.h"
#include <fstream>
#include <string>
#include <vector>

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

	std::cout << file_create_metadata("D:\\University\\critical path.png", 46) << std::endl;
	//fill_header(&res_archive, 0, 0, 0, 0);
	res_archive.close();
}
#endif // DEBUG


/**
* @param newArchName				target file name
* @param newArchNameLen				length of the name of file
* @param inPath						paths to the end files to archive
* @param outPath					where to save the end file
*/
bool MakeArch(char* new_arch_name, int new_arch_name_len, 
	char* in_path, int in_path_len, char* out_path, int out_pathLen, 
	bool use_context_independent_compression, bool use_context_compression)
{
	string arch_name = string(new_arch_name, new_arch_name_len);
	ofstream new_arch(arch_name);

	vector<string> files_names = dispatch_filenames(in_path, in_path_len);
	fill_header(&new_arch, 0, files_names.size(), use_context_compression, use_context_independent_compression, 0);
	
	uint64_t summary_size = 32;
	new_arch.seekp(32);
	for (int i = 0; i < files_names.size(); i++)
	{
		string compressed_data = compress_string(get_file_content(files_names[i]), use_context_independent_compression, use_context_compression, 0);
		string metadata = file_create_metadata(files_names[i], compressed_data.size());
		new_arch << metadata;
		new_arch << compressed_data;
		summary_size += metadata.length() + compressed_data.length();
	}

	fill_header(&new_arch, summary_size, files_names.size(), use_context_compression, use_context_independent_compression, 0);
	return true;
}
