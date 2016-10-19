#pragma once

void GetDictionaryFromFile(std::ifstream & input, std::map<std::string, std::string> & dictionary);

inline std::string GetWord(std::istream & input)
{
	std::string word = "";
	getline(input, word);
	return word;
}