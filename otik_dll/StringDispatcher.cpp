#include "StringDispatcher.h"
#include <vector>
#include <string>

constexpr char DIVIDER = ' ';
constexpr char BRACES = '"';

using std::string;
using std::vector;

vector<string> dispatch_filenames(const char* files_names, int length)
{
	vector<string> res;
	bool string_start = false;
	string temp = "";
	for (int i = 0; i < length; i++)
	{
		if (files_names[i] == BRACES)
		{
			string_start = !string_start;
			if (!string_start)
			{
				res.push_back(temp);
				temp.clear();
			}
			continue;
		}
		if (files_names[i] == DIVIDER)
			continue;

		temp.push_back(files_names[i]);
	}
	return res;
}
