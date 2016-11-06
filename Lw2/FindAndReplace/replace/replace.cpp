#include "stdafx.h"

#include "ReplaceFunctions.h"



int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <search string> <replace string>\n";
		return 1;
	}

	std::string subjectString;
	std::string searchString = argv[1];
	std::string replaceString = argv[2];

	while (!std::cin.eof())
	{
		std::getline(std::cin, subjectString);
		subjectString = FindAndReplace(subjectString, searchString, replaceString);
		std::cout << subjectString << "\n";
	}

    return 0;
}

