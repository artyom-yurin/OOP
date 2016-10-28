#include "stdafx.h"
#include "prime_functions.h"

bool IsNumber(char * str)
{
	for (unsigned i = 0; i < strlen(str); ++i)
	{
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

void PrintSet(std::ostream & output, std::set<int> & printSet)
{
	for (const int & element : printSet)
	{
		output << element << " ";
	}
	output << std::endl;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> numbers(upperBound + 1, true);
	for (int i = 2; i <= upperBound; ++i)
	{
		if (numbers[i])
		{
			for (int j = i; i * j <= upperBound; ++j)
			{
				numbers[i * j] = false;
			}
		}
	}

	std::set<int> primeNumbers;

	for (int i = 2; i <= upperBound; ++i)
	{
		if (numbers[i])
		{
			primeNumbers.emplace_hint(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}