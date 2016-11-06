#include "stdafx.h"
#include "../replace/ReplaceFunctions.h"

BOOST_AUTO_TEST_SUITE(FindAndReplace_function)

	BOOST_AUTO_TEST_CASE(does_not_replace_if_the_search_string_is_empty)
	{
		std::string line = "Hello, name. name is great.";
		std::string replace = "Bob";
		std::string search = "";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), line);
	}

	BOOST_AUTO_TEST_CASE(does_not_replace_if_the_search_string_is_not_found_in_the_text)
	{
		std::string line = "Hello, name. name is great.";
		std::string replace = "Mary";
		std::string search = "Bob";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), line);
	}

	BOOST_AUTO_TEST_CASE(does_not_replace_the_inside_of_the_replaced_text)
	{
		std::string line = "12345";
		std::string replace = "1234";
		std::string search = "234";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), "112345");
	}

	BOOST_AUTO_TEST_CASE(replaces_all_occurrences_of_the_search_string_to_the_string_replacer)
	{
		std::string line = "Hello, name. name is great.";
		std::string replace = "Bob";
		std::string search = "name";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), "Hello, Bob. Bob is great.");
	}

BOOST_AUTO_TEST_SUITE_END()