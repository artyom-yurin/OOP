#include "stdafx.h"
#include "Calc.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

struct CalcFixture
{
	CCalc calc;
};

BOOST_FIXTURE_TEST_SUITE(Calc, CalcFixture)

	BOOST_AUTO_TEST_CASE(variable_declarated)
	{
		BOOST_CHECK(calc.Var("a"));
		BOOST_CHECK(!calc.Var("a"));
		std::map <std::string, double> variables = calc.GetVariables();
		BOOST_CHECK_EQUAL(variables["a"], 0);
	}

	BOOST_AUTO_TEST_CASE(assign_value_to_variable)
	{
		calc.Var("a");
		calc.Var("b");
		BOOST_CHECK(!calc.Let("a", "c"));
		BOOST_CHECK(calc.Let("b", 12));
		BOOST_CHECK(calc.Let("a", "b"));
		std::map <std::string, double> variables = calc.GetVariables();
		BOOST_CHECK_EQUAL(variables["a"], variables["b"]);
	}

	BOOST_AUTO_TEST_CASE(assign_value_to_function)
	{
		calc.Var("d");
		BOOST_CHECK(calc.Fn("a", "d"));
		calc.Let("d", 10);
		std::map <std::string, double*> functions = calc.GetFunctions();
		std::map <std::string, double> variables = calc.GetVariables();
		BOOST_CHECK_EQUAL(*functions["a"], variables["d"]);
	}

	BOOST_AUTO_TEST_CASE(get_function_or_variable)
	{
		calc.Var("a");
		calc.Fn("f", "a");
		calc.Let("a", 10);
		BOOST_CHECK_EQUAL(calc.Get("a"), 10);
		BOOST_CHECK_EQUAL(calc.Get("f"), 10);
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