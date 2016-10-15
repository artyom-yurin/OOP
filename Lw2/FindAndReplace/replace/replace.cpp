#include "stdafx.h"

#include "replace_functions.h"



int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <search string> <replace string>\n";
		return 1;
	}

	std::string subjectString = GetString(std::cin);

	std::string searchString = argv[1];

	if (searchString != "")
	{
		std::string replaceString = argv[2];

		subjectString = FindAndReplace(subjectString, searchString, replaceString);
	}

	if (!PrintString(std::cout, subjectString))
	{
		std::cout << "Failed to save data on disk\n";
		return 1;
	}

    return 0;
}

