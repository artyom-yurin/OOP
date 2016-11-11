#include "stdafx.h"
#include "Index.h"
#include "Variable.h"
#include "Function.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

struct VariableFixture
{
	CVariable variable;
};

BOOST_FIXTURE_TEST_SUITE(Variable, VariableFixture)

	BOOST_AUTO_TEST_CASE(default_value_zero)
	{
		BOOST_CHECK_EQUAL(variable.GetResult(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_set_new_value)
	{
		variable.SetValue(10.0);
		BOOST_CHECK_EQUAL(variable.GetResult(), 10);
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

