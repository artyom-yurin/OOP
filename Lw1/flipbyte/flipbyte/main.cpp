#include <cctype>
#include <iostream>

using namespace std;

namespace
{
	bool IsNumber(char * str)
	{
		for (int i = 0; i < strlen(str); ++i)
		{
			if (!isdigit(str[i])) {
				return false;
			}
		}
		return true;
	}
	
	void FlipByte(uint8_t & byte)
	{
		byte = (byte & 0b01010101 << 1) | (byte & 0b10101010 >> 1);
		byte = (byte & 0b00110011 << 2) | (byte & 0b11001100 >> 2);
		byte = (byte << 4) | (byte >> 4);
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: flipbyte.exe <input byte>\n";
		return 1;
	};
	if ((!IsNumber(argv[1])) || !((atoi(argv[1]) <= 255) && (atoi(argv[1]) >= 0)))
	{
		cout << "Invalid value\n"
			<< "<input byte> must be unsigned int(0 .. 255)\n";
		return 1;
	}

	uint8_t byte = static_cast <uint8_t> (atoi(argv[1]));

	cout << "Input byte: " << argv[1] << endl;
	FlipByte(byte);
	cout << "Output byte: " << static_cast <int> (byte) << endl;
	return 0;
}