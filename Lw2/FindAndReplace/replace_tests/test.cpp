#include "stdafx.h"
#include "../replace/replace_functions.h"

BOOST_AUTO_TEST_SUITE(GetString_function)

	BOOST_AUTO_TEST_CASE(getting_string)
	{
		std::stringstream input("My name is Artem");
		std::string line = GetString(input);
		std::string correctLine = "My name is Artem";
		BOOST_CHECK_EQUAL(line, correctLine);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FindAndReplace_function)

	BOOST_AUTO_TEST_CASE(when_found_substring_replace_it)
	{
		std::string line = "Hello, name. name is great.";
		std::string replace = "Bob";
		std::string search = "name";
		line = FindAndReplace(line, search, replace);
		std::string correctLine = "Hello, Bob. Bob is great.";
		BOOST_CHECK_EQUAL(line, correctLine);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PrintString_function)

	BOOST_AUTO_TEST_CASE(print_string)
	{
		std::stringstream buffer;
		std::string input = "Hello";
		PrintString(buffer, input);
		std::string line;
		getline(buffer, line);
		BOOST_CHECK_EQUAL(line, input);
	}

BOOST_AUTO_TEST_SUITE_END()