#include "stdafx.h"
#include "../Calculator/Variable.h"
#include "../Calculator/Function.h"
#include "../Calculator/Calc.h"

struct VariableFixture
{
	std::shared_ptr<CVariable> pVariable = CVariable::Create();
};

BOOST_FIXTURE_TEST_SUITE(Variable, VariableFixture)

	BOOST_AUTO_TEST_CASE(default_value_NAN)
	{
		BOOST_CHECK(std::isnan(pVariable->GetResult()));
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

	BOOST_AUTO_TEST_CASE(can_not_declare_function_with_with_the_not_creation_indexes)
	{
		BOOST_CHECK_THROW(calc.Fn("fn", "var"), std::invalid_argument);
		BOOST_CHECK_THROW(calc.Fn("var", "var", Sign::plus, "var"), std::invalid_argument);
		calc.Var("var1");
		BOOST_CHECK_THROW(calc.Fn("var", "var1", Sign::plus, "var"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_not_declare_variables_with_busy_name)
	{
		calc.Var("var");
		BOOST_CHECK_THROW(calc.Var("var"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_check_name_on_valid)
	{
		BOOST_CHECK(calc.isValidName("var"));
		BOOST_CHECK(calc.isValidName("v2a_r"));
		BOOST_CHECK(!calc.isValidName("2var"));
		BOOST_CHECK(!calc.isValidName("va r"));
	}
	
	BOOST_AUTO_TEST_CASE(no_default_functions)
	{
		BOOST_CHECK(calc.GetFunctions().empty());
	}

	BOOST_AUTO_TEST_CASE(can_declare_variable)
	{
		calc.Var("var");
		BOOST_CHECK_EQUAL(calc.GetVariables().size(), 1);
	}

	BOOST_AUTO_TEST_CASE(can_print_all_variables)
	{
		calc.Var("var");
		calc.Let("var1", 1);
		calc.Let("var2", 2.45);
		std::stringstream buffer;
		calc.PrintVars(buffer);
		BOOST_CHECK_EQUAL(buffer.str(), "var:nan\nvar1:1.00\nvar2:2.45\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_all_functions)
	{
		calc.Var("var");
		calc.Let("var1", 1);
		calc.Let("var2", 2.45);
		calc.Fn("fn", "var");
		calc.Fn("fn1", "var1");
		calc.Fn("fn2", "var2");
		std::stringstream buffer;
		calc.PrintFns(buffer);
		BOOST_CHECK_EQUAL(buffer.str(), "fn:nan\nfn1:1.00\nfn2:2.45\n");
	}

	BOOST_AUTO_TEST_CASE(can_declare_variable_with_default_value)
	{
		calc.Let("var", 10);
		BOOST_CHECK_EQUAL(calc.GetVariables()["var"]->GetResult(), 10);
	}

	BOOST_AUTO_TEST_CASE(can_not_set_value_for_function)
	{
		calc.Var("var");
		calc.Fn("fn", "var");
		BOOST_CHECK_THROW(calc.Let("fn", 10), std::invalid_argument);
		BOOST_CHECK_THROW(calc.Let("fn", "var"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_not_set_value_with_not_exist_index)
	{
		BOOST_CHECK_THROW(calc.Let("var", "var"), std::invalid_argument);
		calc.Var("var");
		BOOST_CHECK_THROW(calc.Let("var", "var1"), std::invalid_argument);
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
			BOOST_CHECK(std::isnan(calc.GetVariables()["var"]->GetResult()));
			calc.Let("var", 10);
			BOOST_CHECK_EQUAL(calc.GetVariables()["var"]->GetResult(), 10);
		}

		BOOST_AUTO_TEST_CASE(can_set_value_other_variable)
		{
			calc.Let("var", 10);
			calc.Let("var2", "var");
			BOOST_CHECK_EQUAL(calc.GetVariables()["var2"]->GetResult(), calc.GetVariables()["var"]->GetResult());
		}

		BOOST_AUTO_TEST_CASE(can_declare_function)
		{
			calc.Fn("fn", "var");
			calc.Let("var", 10);
			BOOST_CHECK_EQUAL(calc.GetFunctions()["fn"]->GetResult(), calc.GetVariables()["var"]->GetResult());
			calc.Fn("fn1", "var", Sign::plus, "var");
			BOOST_CHECK_EQUAL(calc.GetFunctions()["fn1"]->GetResult(), calc.GetVariables()["var"]->GetResult() * 2);
			calc.Let("var", 90);
			BOOST_CHECK_EQUAL(calc.GetFunctions()["fn1"]->GetResult(), calc.GetVariables()["var"]->GetResult() * 2);
			calc.Fn("fn2", "var", Sign::minus, "fn");
			BOOST_CHECK_EQUAL(calc.GetFunctions()["fn2"]->GetResult(), 0);
		}

		BOOST_AUTO_TEST_CASE(can_not_declare_function_with_employed_name)
		{
			BOOST_CHECK_THROW(calc.Fn("var", "var"), std::invalid_argument);
			BOOST_CHECK_THROW(calc.Fn("var", "var", Sign::plus, "var"), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(can_print_variable_with_nan_value)
		{
			std::stringstream buffer;
			calc.Print(buffer, "var");
			BOOST_CHECK_EQUAL(buffer.str(), "var:nan");
		}

		BOOST_AUTO_TEST_CASE(can_print_variable)
		{
			std::stringstream buffer;
			calc.Let("var", 13.135);
			calc.Print(buffer, "var");
			BOOST_CHECK_EQUAL(buffer.str(), "var:13.13");
		}

		struct declareted_function_ : declareted_variable_
		{
			declareted_function_()
			{
				calc.Fn("fn", "var");
			}
		};

		BOOST_FIXTURE_TEST_SUITE(declareted_function, declareted_function_)

			BOOST_AUTO_TEST_CASE(can_declare_function)
			{
				calc.Fn("fn1", "fn");
				calc.Let("var", 10);
				BOOST_CHECK_EQUAL(calc.GetFunctions()["fn1"]->GetResult(), calc.GetFunctions()["fn"]->GetResult());
				calc.Fn("fn2", "fn1", Sign::plus, "var");
				BOOST_CHECK_EQUAL(calc.GetFunctions()["fn2"]->GetResult(), calc.GetFunctions()["fn1"]->GetResult() + calc.GetVariables()["var"]->GetResult());
				calc.Let("var", 20);
				BOOST_CHECK_EQUAL(calc.GetFunctions()["fn2"]->GetResult(), calc.GetFunctions()["fn1"]->GetResult() + calc.GetVariables()["var"]->GetResult());
				calc.Fn("fn3", "fn1", Sign::minus, "fn");
				BOOST_CHECK_EQUAL(calc.GetFunctions()["fn3"]->GetResult(), 0);
			}
			
			BOOST_AUTO_TEST_CASE(can_print_function_with_nan_value)
			{
				std::stringstream buffer;
				calc.Print(buffer, "fn");
				BOOST_CHECK_EQUAL(buffer.str(), "fn:nan");
			}

			BOOST_AUTO_TEST_CASE(can_print_function)
			{
				std::stringstream buffer;
				calc.Let("var", 13.135);
				calc.Print(buffer, "fn");
				BOOST_CHECK_EQUAL(buffer.str(), "fn:13.13");
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
