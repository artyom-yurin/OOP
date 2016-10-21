#pragma once

std::set<int> GeneratePrimeNumbersSet(int upperBound);

inline void PrintSet(std::ostream & output, std::set<int> & printSet)
{
	for (const int & element : printSet)
	{
		output << element << " ";
	}
	output << std::endl;
}

inline bool IsNumber(char * str)
{
	for (unsigned i = 0; i < strlen(str); ++i)
	{
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}