#include "stdafx.h"

#include "../prime/prime_functions.h"

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)

	BOOST_AUTO_TEST_CASE(correct_data)
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(10);
		std::set<int> correctPrimeNumbers = {
			2, 3, 5, 7
		};
		BOOST_CHECK(primeNumbers == correctPrimeNumbers);
	}

BOOST_AUTO_TEST_SUITE_END()