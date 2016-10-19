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

bool CanFindWord(std::map <std::string, std::string> & dictionary, std::string & word)
{	
	if (dictionary.find(word) != dictionary.end())
	{
		return true;
	}
	else
	{
		for (auto & element : dictionary)
		{
			if (element.second == word)
			{
				return true;
			}
		}
	}
	return false;
}

