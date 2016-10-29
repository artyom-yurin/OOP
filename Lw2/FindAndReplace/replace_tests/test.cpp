#include "stdafx.h"
#include "../replace/replace_functions.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>



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


class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
public:
	SpecLogFormatter() : m_indent(0) {}
private:
	void test_unit_start(std::ostream &os,
		boost::unit_test::test_unit const& tu)
	{
		os << std::string(m_indent, ' ') <<
			boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		m_indent += 2;
	}
	void test_unit_finish(std::ostream &os,
		boost::unit_test::test_unit const& tu, unsigned long elapsed)
	{
		elapsed;
		tu;
		os;
		m_indent -= 2;
	}
	int m_indent;
};


boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
