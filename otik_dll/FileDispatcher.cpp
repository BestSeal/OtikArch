#include "pch.h"
#include "StringDispatcher.h"
#include <string>
#include <fstream>
#include <filesystem>

using std::string;
using std::ofstream;

string file_create_metadata(string filepath_s, uint64_t filesize)
{
	uint16_t metadata_size = 16 + 64 + filepath_s.size();
	string res = string();
	
	res.append(16 - std::to_string(metadata_size).length(), '0');
	res.append(std::to_string(metadata_size));

	res.append(64 - std::to_string(filesize).length(), '0');
	res.append(std::to_string(filesize));

	res.append(filepath_s);

	return res;
}

string get_file_content(string path_to_file)
{
	std::ifstream file = std::ifstream(path_to_file);
	string content((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	return content;
}

string compress_string(string input, bool contxtindepc, bool contxtdepc, bool protection)
{
	return input;
}
