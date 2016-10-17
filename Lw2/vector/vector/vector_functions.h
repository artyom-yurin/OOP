#pragma once

inline std::vector <double> GetNumbers(std::istream & input)
{
	std::vector <double> result;
	copy(std::istream_iterator <double>(input), std::istream_iterator <double>(), back_inserter(result));
	return result;
}

inline auto GetMaxMinElement(const std::vector <double> & numbers)
{
	return std::minmax_element(numbers.begin(), numbers.end());
}

double GetMultiplier(const std::vector <double> & numbers);

void ProcessVector(std::vector <double> & numbers);

void PrintVector(std::ostream & output, const std::vector <double> & numbers);