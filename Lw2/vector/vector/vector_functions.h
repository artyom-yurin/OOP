#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <iterator>
#include <iostream>

std::vector <double> GetNumbers(std::istream & input)
{
	std::vector <double> result;
	copy(std::istream_iterator <double>(input), std::istream_iterator <double>(), back_inserter(result));
	return result;
}

auto GetMaxMinElement(const std::vector <double> & numbers)
{
	return std::minmax_element(numbers.begin(), numbers.end());
}

double GetMultiplier(const std::vector <double> & numbers)
{
	auto minMax = GetMaxMinElement(numbers);
	double result = *minMax.second;

	if (*minMax.first != 0)
	{
		result /= *minMax.first;
	}

	return result;
}

void ProcessVector(std::vector <double> & numbers)
{
	if (numbers.empty())
	{
		return;
	}

	double multiplier = GetMultiplier(numbers);

	transform(numbers.begin(), numbers.end(), numbers.begin(), [=](double element) {
		return element * multiplier;
	});
}

void PrintVector(std::ostream & output, const std::vector <double> & numbers)
{
	for (const double & element : numbers)
	{
		output << std::fixed << std::setprecision(3) << element << " ";
	}
	output << std::endl;
}
