#include "stdafx.h"
#include "prime_functions.h"

int main(int argc, char * argv [])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <upper bound>\n";
		return 1;
	}

	if ((atoi(argv[1]) > 100000000) || (atoi(argv[1]) < 2))
	{
		std::cout << "Invalid value\n"
			<< "Upper bound must be from 2 to 100000000\n";
		return 1;
	}

	int upperBound = atoi(argv[1]);

	std::set<int> primeNumbers;

	//TODO: Get Prime Numbers Set

	PrintSet(std::cout, primeNumbers);

    return 0;
}

