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

	std::replace(filepath_s.begin(), filepath_s.end(), '\\', '/');
	res.append(filepath_s);

	return res;
}

string get_file_content(string path_to_file)
{
	std::ifstream file = std::ifstream(path_to_file, std::ios_base::binary);

	string content((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	//string content = string();
	return content;
}

string get_rel_path_of_files(std::vector<string> file_names)
{
	string res = std::filesystem::path(file_names[0]).parent_path().string();
	for (string file_name : file_names)
	{
		string path = std::filesystem::path(file_name).parent_path().string();
		if (std::filesystem::is_regular_file(file_name) && res.length() > file_name.length())
			res = path;
	}
	return res;
}

string get_rel_path_of_file(string file_name, string rel_path)
{
	file_name.erase(file_name.begin(), file_name.begin() + rel_path.length() + 1);
	return file_name;
}

string compress_string(string input, bool contxtindepc, bool contxtdepc, bool protection)
{
	return input;
}

string uncompress_string(string input, bool contxtindepc, bool contxtdepc, bool protection)
{
	return input;
}
