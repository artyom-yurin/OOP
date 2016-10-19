#include "stdafx.h"
#include "dictionary_functions.h"

void GetDictionaryFromFile(std::ifstream & input, std::map<std::string, std::string> & dictionary)
{
	std::string key = "";
	std::string value = "";
	while (getline(input, key, ':') && getline(input, value, '\n'))
	{
		dictionary[key] = value;
	}
}

