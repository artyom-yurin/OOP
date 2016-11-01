#include "stdafx.h"

#include "../vector/vector_functions.h"
#include <boost/test/included/unit_test.hpp>

#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>


BOOST_AUTO_TEST_SUITE(GetNumbers_function)

	BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_buffer)
	{
		std::stringstream input("");
		auto numbers = GetNumbers(input);
		BOOST_CHECK(numbers.empty());
	}
	
	BOOST_AUTO_TEST_SUITE(when_buffer_contains_data_incorrectly)
	
		BOOST_AUTO_TEST_CASE(should_considered_to_incorrectly_data)
		{
			std::stringstream input("5 4 3 1 2 A r t e m");
			auto numbers = GetNumbers(input);
			const std::vector <double> correctNumbers = {
				5, 4, 3, 1, 2
			};
			BOOST_CHECK(numbers == correctNumbers);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_buffer_contains_data_correctly)

		BOOST_AUTO_TEST_CASE(should_considered_int_data)
		{
			std::stringstream input("5 4 3 1 2");
			auto numbers = GetNumbers(input);
			const std::vector <double> correctNumbers = {
				5, 4, 3, 1, 2
			};
			BOOST_CHECK(numbers == correctNumbers);
		}

		BOOST_AUTO_TEST_CASE(should_considered_float_data)
		{
			std::stringstream input("1.01 2.31 3.12 3.1 3.4");
			auto numbers = GetNumbers(input);
			const std::vector <double> correctNumbers = {
				1.01, 2.31, 3.12, 3.1, 3.4
			};
			BOOST_CHECK(numbers == correctNumbers);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GetMinAndMax_function)
	
	BOOST_AUTO_TEST_CASE(should_find_int_min_and_max)
	{
		const std::vector <double> input = {
			1, 2, 3, 4, 5
		};
		auto result = GetMaxMinElement(input);
		double correctMin = 1;
		double correctMax = 5;
		BOOST_CHECK_EQUAL(*result.first, correctMin);
		BOOST_CHECK_EQUAL(*result.second, correctMax);
	}

	BOOST_AUTO_TEST_CASE(should_find_float_min_and_max)
	{
		const std::vector <double> input = {
			0.12, 2.3, 3.1, 2.45
		};
		auto result = GetMaxMinElement(input);
		double correctMin = 0.12;
		double correctMax = 3.1;
		BOOST_CHECK_EQUAL(*result.first, correctMin);
		BOOST_CHECK_EQUAL(*result.second, correctMax);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GetMultiplier_function)

	BOOST_AUTO_TEST_CASE(when_min_equal_zero)
	{
		const std::vector <double> input = {
			0, 1, 2, 3, 4
		};
		auto multiplier = GetMultiplier(input);
		double correctMultiplier = 4;
		BOOST_CHECK_EQUAL(correctMultiplier, multiplier);
	}

	BOOST_AUTO_TEST_CASE(when_data_correct)
	{
		const std::vector <double> input = {
			6, 5, 2, 3, 4
		};
		auto multiplier = GetMultiplier(input);
		double correctMultiplier = 3;
		BOOST_CHECK_EQUAL(correctMultiplier, multiplier);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	BOOST_AUTO_TEST_CASE(when_min_equal_zero)
	{
		std::vector <double> input = {
			0, 1, 2, 3, 4
		};
		ProcessVector(input);
		const std::vector <double> correctInput = {
			0, 4, 8, 12, 16
		};
		BOOST_CHECK(correctInput == input);
	}
	
	BOOST_AUTO_TEST_CASE(correct_data)
	{
		std::vector <double> input = {
			6, 5, 2, 3, 4
		};
		ProcessVector(input);
		const std::vector <double> correctInput = {
			18, 15, 6, 9, 12
		};
		BOOST_CHECK(correctInput == input);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PrintVector_function)

	BOOST_AUTO_TEST_CASE(empty_vector)
	{
		std::stringstream buffer;
		const std::vector <double> input = {};
		PrintVector(buffer, input);
		std::string line;
		getline(buffer, line);
		BOOST_CHECK_EQUAL(line, "");
	}

	BOOST_AUTO_TEST_CASE(when_vector_not_empty)
	{
		std::stringstream buffer;
		const std::vector <double> input = {
			1.112, 2.312, 3.2, 4, 5.23
		};
		PrintVector(buffer, input);
		std::string line;
		getline(buffer, line);
		BOOST_CHECK_EQUAL(line, "1.112 2.312 3.200 4.000 5.230 ");
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
