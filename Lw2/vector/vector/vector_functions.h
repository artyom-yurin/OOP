#pragma once

#include "stdafx.h"

using namespace std;

vector <double> GetNumbers(istream & input)
{
	vector <double> result;
	copy(istream_iterator <double>(input), istream_iterator <double>(), back_inserter(result));
	return result;
}

auto GetMaxMinElement(const vector <double> & numbers)
{
	return minmax_element(numbers.begin(), numbers.end());
}

double GetMultiplier(const vector <double> & numbers)
{
	auto minMax = GetMaxMinElement(numbers);
	double result = *minMax.second;

	if (*minMax.first != 0)
	{
		result /= *minMax.first;
	}

	return result;
}

void ProcessVector(vector <double> & numbers)
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

void PrintVector(ostream & output, const vector <double> & numbers)
{
	for (const double & element : numbers)
	{
		output << std::fixed << std::setprecision(3) << element << " ";
	}
	output << std::endl;
}
