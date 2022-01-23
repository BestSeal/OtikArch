#include <string>
#include "pch.h"

std::string file_create_metadata(std::string filepath_s, uint64_t filesize);
std::string get_file_content(std::string path_to_file);
std::string compress_string(std::string input, bool contxtindepc, bool contxtdepc, bool protection);
std::string uncompress_string(std::string input, bool contxtindepc, bool contxtdepc, bool protection);
std::string get_rel_path_of_files(std::vector<std::string> file_names);
std::string get_rel_path_of_file(std::string file_name, std::string rel_path);
