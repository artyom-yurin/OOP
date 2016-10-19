#include "stdafx.h"
#include "dictionary_functions.h"

int main(int argc, char * argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
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
		if (CheckExit(word))
		{
			//TODO: Save dictionary
			return 0;
		}
		if (!GetTranslate(dictionary, word))
		{
			//TODO: add new word
		}
	}
}