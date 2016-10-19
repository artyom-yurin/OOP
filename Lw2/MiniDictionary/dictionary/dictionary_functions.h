#pragma once

void GetDictionaryFromFile(std::ifstream & input, std::map <std::string, std::string> & dictionary);

inline std::string GetWord(std::istream & input)
{
	std::string word = "";
	getline(input, word);
	//TODO: transform to lower case
	return word;
}

bool CanFindWord(std::map <std::string, std::string> & dictionary, std::string & word);