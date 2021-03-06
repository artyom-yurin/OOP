#pragma once

void GetDictionaryFromFile(std::ifstream & input, std::map <std::string, std::string> & dictionary);

inline std::string GetWord(std::istream & input)
{
	std::string word = ""; 
	getline(input, word);
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	return word;
}

bool CheckExit(const std::string & word);

bool AddNewWord(std::istream & input, std::ostream & output, std::map <std::string, std::string> & dictionary, const std::string & key);

bool GetTranslate(std::ostream & output, const std::map <std::string, std::string> & dictionary, const std::string & word);

bool SaveAnswer();

void SaveDictionaryInFile(const std::map <std::string, std::string> & dictionary, std::ofstream & output);