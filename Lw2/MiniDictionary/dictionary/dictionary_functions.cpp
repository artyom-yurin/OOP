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

bool CheckExit(std::string & word)
{
	return word == "...";
}

bool AddNewWord(std::map<std::string, std::string>& dictionary, std::string & key)
{
	std::string value = "";
	std::cout << "¬ведите перевод слова: ";
	getline(std::cin, value);
	if (value.empty())
	{
		return false;
	}
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);
	dictionary[key] = value;
	return true;
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

