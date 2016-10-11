#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

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

 uint8_t MixBitsCrypt(const uint8_t byte)
{
	 uint8_t result = 0;
	 result |= (byte & 0b10000000 >> 2);
	 result |= (byte & 0b00011000 << 3);
	 result |= (byte & 0b00000111 << 2);
	 result |= (byte & 0b01100000 >> 5);
	 return result;
}

uint8_t MixBitsDecrypt(const uint8_t byte)
{
	uint8_t result = 0;
	result |= (byte & 0b00100000 << 2);
	result |= (byte & 0b11000000 >> 3);
	result |= (byte & 0b00011100 >> 2);
	result |= (byte & 0b00000011 << 5);
	return result;
}

bool CryptFile(ifstream & input, ofstream & output, const uint8_t key)
{
	string currentString = "";
	while (getline(input, currentString))
	{
		for (size_t i = 0; i < currentString.length(); ++i)
		{
			currentString[i] ^= key;
			MixBitsCrypt(currentString[i]);
		}

		if (!(output << currentString << "\n"))
		{
			return false;
		}
	}
	return true;
}

bool DecryptFile(ifstream & input, ofstream & output, const uint8_t key)
{
	string currentString = "";
	while (getline(input, currentString))
	{
		for (size_t i = 0; i < currentString.length(); ++i)
		{
			MixBitsDecrypt(currentString[i]);
			currentString[i] ^= key;
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
	int workMode;
	string mode = argv[1];
	if (mode == "crypt")
	{
		workMode = CRYPT;
	} 
	else if (mode == "decrypt")
	{
		workMode = DECRYPT;
	}
	else
	{
		cout << "Unknown mode\n"
			<< "Usage: crypt or decrypt\n";
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

	if (!IsNumber(argv[4]))
	{
		cout << "Key must be number\n";
		return 1;
	}

	if (!((atoi(argv[4]) >= 0) && (atoi(argv[4]) <= 255)))
	{
		cout << "Key must be for 0 to 255\n";
		return 1;
	}
	uint8_t key = atoi(argv[4]);

	if (workMode == CRYPT)
	{
		if (!CryptFile(input, output, key))
		{
			cout << "Failed to save data on disk\n";
			return 1;
		}
	}
	else
	{
		if (!DecryptFile(input, output, key))
		{
			cout << "Failed to save data on disk\n";
			return 1;
		}
	}
	

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}