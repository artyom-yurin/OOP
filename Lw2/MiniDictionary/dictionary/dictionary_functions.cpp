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

bool CheckExit(const std::string & word)
{
	return word == "...";
}

bool AddNewWord(std::map<std::string, std::string>& dictionary, const std::string & key)
{
	std::string value = "";
	std::cout << "Введите перевод слова: ";
	getline(std::cin, value);
	if (value.empty())
	{
		std::cout << "Слово \"" << key << "\" было проигнорировано.\n";
		return false;
	}
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);
	dictionary[key] = value;
	return true;
}

bool GetTranslate(const std::map <std::string, std::string> & dictionary, const std::string & word)
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

bool SaveAnswer()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	std::string answer = "";
	std::cin >> answer;
	if (answer == "Y" || answer == "y")
	{
		return true;
	}
	return false;
}

void SaveDictionaryInFile(const std::map<std::string, std::string>& dictionary, std::ofstream & output)
{
	for (auto it = dictionary.begin(); it != dictionary.end(); it++)
	{
		output << it->first << ":" << it->second << "\n";
	}
}

