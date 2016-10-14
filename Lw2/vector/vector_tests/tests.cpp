#include "stdafx.h"

#include "../vector/vector_functions.h"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(Get_Numbers)
{
	{
		std::stringstream input("1 2 3 4 5");
		auto numbers = GetNumbers(input);
		const vector <double> correctNumbers = {
			1, 2, 3, 4, 5
		};
		BOOST_CHECK(numbers == correctNumbers);
	}

	{
		std::stringstream input("5 4 3 1 2 A r t e m 1 2 3");
		auto numbers = GetNumbers(input);
		const vector <double> correctNumbers = {
			5, 4, 3, 1, 2
		};
		BOOST_CHECK(numbers == correctNumbers);
	}
	
	{
		std::stringstream input("5 4 3 1 2 A r t e m");
		auto numbers = GetNumbers(input);
		const vector <double> correctNumbers = {
			5, 4, 3, 1, 2
		};
		BOOST_CHECK(numbers == correctNumbers);
	}

	{
		std::stringstream input("");
		auto numbers = GetNumbers(input);
		const vector <double> correctNumbers = {};
		BOOST_CHECK(numbers == correctNumbers);
	}

	{
		std::stringstream input("1.01 2.31 3.12 3.1 3.4");
		auto numbers = GetNumbers(input);
		const vector <double> correctNumbers = {
			1.01, 2.31, 3.12, 3.1, 3.4
		};
		BOOST_CHECK(numbers == correctNumbers);
	}
}

BOOST_AUTO_TEST_SUITE_END()
