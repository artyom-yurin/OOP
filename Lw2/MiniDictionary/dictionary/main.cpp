#include "stdafx.h"
#include "dictionary_functions.h"

int main(int argc, char * argv[])
{
	setlocale(0, ""); 
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
	bool NeedSaveDictionary = false;
	while (true)
	{
		std::cout << "������� �����: ";
		std::string word = GetWord(std::cin);
		if (CheckExit(word))
		{
			if (NeedSaveDictionary)
			{
				if (SaveAnswer())
				{
					std::ofstream newDictionaryFile;
					if (argc == 2)
					{
						newDictionaryFile.open(argv[1]);
					}
					else
					{
						newDictionaryFile.open("dictionary.txt");
					}
					SaveDictionaryInFile(dictionary, newDictionaryFile);
					std::cout << "��������� ���� ���������. �� ��������\n";
				}
				else
				{
					std::cout << "��������� �� ���� ���������. �� ��������\n";
				}
			}
			else
			{
				std::cout << "�� ��������\n";
			}
			return 0;
		}

		if (!GetTranslate(std::cout, dictionary, word))
		{
			std::cout << "����������� ����� \"" << word << "\".\n";
			std::cout << "������� ������� �����: ";
			if (AddNewWord(std::cin, std::cout, dictionary, word))
			{
				std::cout << "����� \"" << word << "\" ��������� � ������� ��� \"" << dictionary[word] << "\".\n";
				NeedSaveDictionary = true;
			}
		}
	}
}