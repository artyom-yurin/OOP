#include "stdafx.h"
#include "vector_functions.h"

using namespace std;

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
