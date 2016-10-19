#include "stdafx.h"
#include "dictionary_functions.h"

void GetDictionaryFromFile(std::ifstream & input, std::map <std::string, std::string> & dictionary)
{
	std::string key = "";
	std::string value = "";
	while (getline(input, key, ':') && getline(input, value, '\n'))
	{
		dictionary[key] = value;
	}
}

bool CheckExit(std::string word)
{
	return word == "...";
}

bool GetTranslate(std::map <std::string, std::string> & dictionary, std::string & word)
{	
	if (dictionary.find(word) != dictionary.end())
	{
		std::cout << dictionary.find(word)->second << "\n";
		return true;
	}
	else
	{
		for (auto & element : dictionary)
		{
			if (element.second == word)
			{
				std::cout << element.first << "\n";
				return true;
			}
		}
	}
	return false;
}

