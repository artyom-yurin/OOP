#include "stdafx.h"
#include "../replace/replace_functions.h"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(Get_string)
{
	std::stringstream input("My name is Artem");
	std::string line = GetString(input);
	std::string correctLine = "My name is Artem";
	BOOST_CHECK(line == correctLine);
}

BOOST_AUTO_TEST_CASE(Find_and_replace_string)
{
	std::string line = "Hello, name. name is great.";
	std::string replace = "Bob";
	std::string search = "name";
	line = FindAndReplace(line, search, replace);
	std::string correctLine = "Hello, Bob. Bob is great.";
	BOOST_CHECK(line == correctLine);
}

BOOST_AUTO_TEST_CASE(Print_string)
{
	std::stringstream buffer;
	std::string input = "Hello";
	PrintString(buffer, input);
	std::string line;
	getline(buffer, line);
	BOOST_CHECK(line == input);
}

BOOST_AUTO_TEST_SUITE_END()