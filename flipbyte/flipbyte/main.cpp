#include <cctype>
#include <iostream>

using namespace std;

namespace
{
	void flipByte(uint8_t & byte)
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
	}

	if ((atoi(argv[1]) > 255) &&
		(atoi(argv[1]) < 0) &&
		(!isdigit(atoi(argv[1]))))
	{
		cout << "Invalid value\n"
			<< "<input byte> must be unsign int(0 .. 255)\n";
	}

	uint8_t byte = static_cast <uint8_t> (atoi(argv[1]));

	printf("Input byte: %u\n", byte);
	flipByte(byte);
	printf("Output byte: %u\n", byte);
	return 0;
}