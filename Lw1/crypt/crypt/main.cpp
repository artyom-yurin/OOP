#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int CRYPT = 0;
const int DECRYPT = 1;


bool IsNumber(char * str)
{
	for (size_t i = 0; i < strlen(str); ++i)
	{
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

void XorString(string & inputString, const int key)
{
	for (size_t i = 0; i < inputString.length(); ++i)
	{
		inputString[i] = inputString[i] ^ key;
	}
}

bool CryptFile(ifstream & input, ofstream & output, const int key, const int mode)
{
	string currentString = "";
	while (getline(input, currentString))
	{
		if (mode == CRYPT)
		{
			XorString(currentString, key);
			//Swap bits
		}
		else
		{
			//Swap bits
			XorString(currentString, key);
		}

		if (!(output << currentString << "\n"))
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char * argv [])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: crypt.exe crypt <input file> <output file> <key>\n"
			<< "or\n"
			<< "crypt.exe decrypt <input file> <output file> <key>\n";
		return 1;
	}
	int mode;
	if (argv[1] = "crypt")
	{
		mode = CRYPT;
	} 
	else if (argv[1] = "decrypt")
	{
		mode = DECRYPT;
	}
	else
	{
		cout << "Unknown mode\n";
		return 1;
	}

	ifstream input(argv[2]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	ofstream output(argv[3]);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[3] << " for writing\n";
		return 1;
	}

	if (!IsNumber(argv[4]) && ((atoi(argv[4]) >= 0) && (atoi(argv[4]) <= 255)))
	{
		cout << "Key must be 0 to 255\n";
		return 1;
	}
	int key = atoi(argv[4]);

	if (!CryptFile(input, output, key, mode))
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}