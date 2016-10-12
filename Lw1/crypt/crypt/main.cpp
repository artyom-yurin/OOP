#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

enum class Mode {Crypt, Decrypt, Unknown};

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

bool CryptFile(ifstream & input, ofstream & output, const uint8_t key, Mode mode)
{
	string currentString = "";
	while (getline(input, currentString))
	{
		for (size_t i = 0; i < currentString.size(); ++i)
		{
			if (mode == Mode::Crypt)
			{
				currentString[i] ^= key;
				MixBitsCrypt(currentString[i]);
			}
			else
			{
				currentString[i] ^= key;
				MixBitsDecrypt(currentString[i]);
			}
		}

		if (!(output << currentString << "\n"))
		{
			return false;
		}
	}
	return true;
}

Mode DetermineMode(char * inputMode)
{
	string mode = inputMode;

	if (mode == "crypt")
	{
		return Mode::Crypt;
	}
	else if (mode == "decrypt")
	{
		return Mode::Decrypt;
	}
	else
	{
		return Mode::Unknown;
	}
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
	Mode workMode = DetermineMode(argv[1]);
	
	if (workMode == Mode::Unknown)
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

	if (!CryptFile(input, output, key, workMode))
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