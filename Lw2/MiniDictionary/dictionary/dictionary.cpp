#include "stdafx.h"
#include "dictionary_functions.h"

int main(int argc, char * argv[])
{
	std::map<std::string, std::string> dictionary;
	if (argc == 2)
	{
		std::ifstream dictionaryFile(argv[1]);
		if (dictionaryFile.is_open())
		{
			GetDictionaryFromFile(dictionaryFile, dictionary);
		}
	}

	while (true)
	{
		std::string word = GetWord(std::cin);
	}

	return 0;
}