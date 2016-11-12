#include "stdafx.h"
#include "Index.h"
#include "Variable.h"
#include "Function.h"
#include "Calc.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

struct VariableFixture
{
	std::shared_ptr<CVariable> pVariable = CVariable::Create();
};

BOOST_FIXTURE_TEST_SUITE(Variable, VariableFixture)

	BOOST_AUTO_TEST_CASE(default_value_0)
	{
		BOOST_CHECK_EQUAL(pVariable->GetResult(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_set_new_value)
	{
		pVariable->SetValue(10.0);
		BOOST_CHECK_EQUAL(pVariable->GetResult(), 10);
	}

	struct when_default_value_set_
	{
		std::shared_ptr<CVariable> pVariable = CVariable::Create(10);
	};

	BOOST_FIXTURE_TEST_SUITE(when_default_value_set, when_default_value_set_)

		BOOST_AUTO_TEST_CASE(default_value_10)
		{
			BOOST_CHECK_EQUAL(pVariable->GetResult(), 10);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

struct FunctionFixture : VariableFixture
{
	std::shared_ptr<CFunction> pFunction = CFunction::Create(pVariable);
};

BOOST_FIXTURE_TEST_SUITE(Function, FunctionFixture)

	BOOST_AUTO_TEST_CASE(value_equal_variable_value)
	{
		BOOST_CHECK_EQUAL(pFunction->GetResult(), pVariable->GetResult());
		pVariable->SetValue(100);
		pFunction->Refresh();
		BOOST_CHECK_EQUAL(pFunction->GetResult(), pVariable->GetResult());
	}

	struct when_function_equal_expression_
	{
		std::shared_ptr<CVariable> pVariable = CVariable::Create(10);
		std::shared_ptr<CVariable> p2Variable = CVariable::Create(30);
		std::shared_ptr<CFunction> pFunction = CFunction::Create(pVariable, Sign::plus, p2Variable);
	};

	BOOST_FIXTURE_TEST_SUITE(when_function_equal_expression, when_function_equal_expression_)

		BOOST_AUTO_TEST_CASE(value_equal_expression_value)
		{
			BOOST_CHECK_EQUAL(pFunction->GetResult(), pVariable->GetResult() + p2Variable->GetResult());
		}

		BOOST_AUTO_TEST_CASE(zero_can_not_be_divided)
		{
			p2Variable->SetValue(0);
			pFunction = CFunction::Create(pVariable, Sign::divider, p2Variable);
			BOOST_CHECK_EQUAL(pFunction->GetResult(), pVariable->GetResult());
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

struct CalcFixture
{
	CCalc calc;
};

BOOST_FIXTURE_TEST_SUITE(Calculator, CalcFixture)

	BOOST_AUTO_TEST_CASE(no_default_variables)
	{
		BOOST_CHECK(calc.GetVariables().empty());
	}

	BOOST_AUTO_TEST_CASE(no_default_functions)
	{
		BOOST_CHECK(calc.GetFunctions().empty());
	}

	BOOST_AUTO_TEST_CASE(can_declare_variable)
	{
		calc.Var("var");
		BOOST_CHECK_EQUAL(calc.GetVariables()["var"]->GetResult(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_declare_variable_with_default_value)
	{
		calc.Let("var", 10);
		BOOST_CHECK_EQUAL(calc.GetVariables()["var"]->GetResult(), 10);
	}

	struct declareted_variable_ : CalcFixture
	{
		declareted_variable_()
		{
			calc.Var("var");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(declareted_variable, declareted_variable_)

		BOOST_AUTO_TEST_CASE(can_set_value)
		{
			BOOST_CHECK_EQUAL(calc.GetVariables()["var"]->GetResult(), 0);
			calc.Let("var", 10);
			BOOST_CHECK_EQUAL(calc.GetVariables()["var"]->GetResult(), 10);
		}

	BOOST_AUTO_TEST_SUITE_END()

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

