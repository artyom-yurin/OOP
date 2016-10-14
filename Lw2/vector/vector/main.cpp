#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <iterator>

using namespace std;

vector <double> GetNumbers(istream & input)
{
	vector <double> result;
	copy(istream_iterator <double> (input), istream_iterator <double> (), back_inserter(result));
	return result;
}

auto GetMaxMinElement(const vector <double> & numbers)
{
	return minmax_element(numbers.begin(), numbers.end());
}

void ProcessVector(vector <double> & numbers)
{
	if (numbers.empty())
	{
		return;
	}
	auto minMax = GetMaxMinElement(numbers);
	double multiplier = *minMax.second;
	if (*minMax.first != 0)
	{
		multiplier /= *minMax.first;
	}
	transform(numbers.begin(), numbers.end(), numbers.begin(), [=](double element){
		return element * multiplier;
	});
}

void PrintVector(ostream & output, vector <double> & numbers)
{
	for (const double & element : numbers)
	{
		output << std::fixed << std::setprecision(3) << element << " ";
	}
	output << std::endl;
}

int main(int argc, char * argv[])
{
	vector <double> numbers = GetNumbers(cin);

	ProcessVector(numbers);

	sort(numbers.begin(), numbers.end(), [](double a, double b) {
		return a < b;
	});

	PrintVector(cout, numbers);

	return 0;
}
