#include "stdafx.h"
#include "../replace/replace_functions.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

BOOST_AUTO_TEST_SUITE(FindAndReplace_function)

	BOOST_AUTO_TEST_CASE(when_search_substring_empty)
	{
		std::string line = "Hello, name. name is great.";
		std::string replace = "Bob";
		std::string search = "";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), line);
	}

	BOOST_AUTO_TEST_CASE(when_search_substring_not_search_in_string)
	{
		std::string line = "Hello, name. name is great.";
		std::string replace = "Mary";
		std::string search = "Bob";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), line);
	}

	BOOST_AUTO_TEST_CASE(when_search_substring_is_part_replace_substirng)
	{
		std::string line = "12345";
		std::string replace = "1234";
		std::string search = "234";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), "112345");
	}

	BOOST_AUTO_TEST_CASE(when_search_substring_search_in_string)
	{
		std::string line = "Hello, name. name is great.";
		std::string replace = "Bob";
		std::string search = "name";
		BOOST_CHECK_EQUAL(FindAndReplace(line, search, replace), "Hello, Bob. Bob is great.");
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
