#include "stdafx.h"

#include "../vector/vector_functions.h"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(Get_Numbers)
{
	{
		std::stringstream input("1 2 3 4 5");
		auto numbers = GetNumbers(input);
		const std::vector <double> correctNumbers = {
			1, 2, 3, 4, 5
		};
		BOOST_CHECK(numbers == correctNumbers);
	}

	/*{
		std::stringstream input("5 4 3 1 2 A r t e m 1 2 3");
		auto numbers = GetNumbers(input);
		const std::vector <double> correctNumbers = {
			5, 4, 3, 1, 2
		};
		BOOST_CHECK_EQUAL(numbers, correctNumbers);
	}
	
	{
		std::stringstream input("5 4 3 1 2 A r t e m");
		auto numbers = GetNumbers(input);
		const std::vector <double> correctNumbers = {
			5, 4, 3, 1, 2
		};
		BOOST_CHECK_EQUAL(numbers, correctNumbers);
	}

	{
		std::stringstream input("");
		auto numbers = GetNumbers(input);
		BOOST_CHECK(numbers.empty());
	}

	{
		std::stringstream input("1.01 2.31 3.12 3.1 3.4");
		auto numbers = GetNumbers(input);
		const std::vector <double> correctNumbers = {
			1.01, 2.31, 3.12, 3.1, 3.4
		};
		BOOST_CHECK_EQUAL(numbers, correctNumbers);
	}*/
}
//
BOOST_AUTO_TEST_CASE(Get_Min_And_Max)
{
	{
		const std::vector <double> input = {
			1, 2, 3, 4, 5
		};
		auto result = GetMaxMinElement(input);
		double correctMin = 1;
		double correctMax = 5;
		BOOST_CHECK(*result.first == correctMin);
		BOOST_CHECK(*result.second == correctMax);
	}
//
//	{
//		const std::vector <double> input = {
//			0.12, 2.3, 3.1, 2.45
//		};
//		auto result = GetMaxMinElement(input);
//		double correctMin = 0.12;
//		double correctMax = 3.1;
//		BOOST_CHECK(*result.first == correctMin);
//		BOOST_CHECK(*result.second == correctMax);
//	}
//}
//
//BOOST_AUTO_TEST_CASE(Get_Multiplier)
//{
//	{
//		const std::vector <double> input = {
//			1, 2, 3, 4, 5
//		};
//		auto multiplier = GetMultiplier(input);
//		double correctMultiplier = 5;
//		BOOST_CHECK(correctMultiplier == multiplier);
//	}
//
//	{
//		const std::vector <double> input = {
//			0, 1, 2, 3, 4
//		};
//		auto multiplier = GetMultiplier(input);
//		double correctMultiplier = 4;
//		BOOST_CHECK(correctMultiplier == multiplier);
//	}
}
//
BOOST_AUTO_TEST_CASE(Process_Vector)
{
	{
		std::vector <double> input = {};
		ProcessVector(input);
		BOOST_CHECK(input.empty());
	}
//
//	{
//		std::vector <double> input = {
//			0, 1, 2, 3, 4
//		};
//		ProcessVector(input);
//		const std::vector <double> correctInput = {
//			0, 4, 8, 12, 16
//		};
//		BOOST_CHECK(correctInput == input);
//	}
//
//	{
//		std::vector <double> input = {
//			5, 6, 2, 3, 4
//		};
//		ProcessVector(input);
//		const std::vector <double> correctInput = {
//			15, 18, 6, 9, 12
//		};
//		BOOST_CHECK(correctInput == input);
//	}
}
//
BOOST_AUTO_TEST_CASE(Print_Vector)
{
	{
		std::stringstream buffer;
		const std::vector <double> input = {};
		PrintVector(buffer, input);
		std::string line;
		getline(buffer, line);
		BOOST_CHECK(line == "");
	}
//
//	{
//		std::stringstream buffer;
//		const std::vector <double> input = {
//			1, 2, 3, 4, 5
//		};
//		PrintVector(buffer, input);
//		std::string line;
//		getline(buffer, line);
//		BOOST_CHECK(line == "1.000 2.000 3.000 4.000 5.000 ");
//	}
//
//	{
//		std::stringstream buffer;
//		const std::vector <double> input = {
//			1.112, 2.312, 3.2, 4, 5.23
//		};
//		PrintVector(buffer, input);
//		std::string line;
//		getline(buffer, line);
//		BOOST_CHECK(line == "1.112 2.312 3.200 4.000 5.230 ");
//	}
}

BOOST_AUTO_TEST_SUITE_END()
