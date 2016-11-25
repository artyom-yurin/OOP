#include "stdafx.h"
#include "../RationalNumbers/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(rational_can_be_converted_to_double)
	{
		CRational r(3, 5);
		BOOST_CHECK_EQUAL(r.ToDouble(), 0.6);
	}

	BOOST_AUTO_TEST_CASE(has_unary_plus_that_return_itself)
	{
		VerifyRational(+CRational(3, 5), 3, 5);
		VerifyRational(+CRational(-3, 5), -3, 5);
	}

	BOOST_AUTO_TEST_CASE(has_unary_minus_that_negates_itself)
	{
		VerifyRational(-CRational(3, 5), -3, 5);
		VerifyRational(-CRational(-3, 5), 3, 5);
	}

	BOOST_AUTO_TEST_CASE(has_binary_addition_operation)
	{
		VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 2) + 1, 3, 2);
		VerifyRational(1 + CRational(1, 2), 3, 2);
	}

	BOOST_AUTO_TEST_CASE(has_binary_subtraction_operation)
	{
		VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
		VerifyRational(CRational(1, 2) - 1, -1, 2);
		VerifyRational(1 - CRational(1, 2), 1, 2);
	}

	BOOST_AUTO_TEST_CASE(has_adding_assignment_operator)
	{
		VerifyRational(CRational(1, 2) += CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 2) += 1, 3, 2);
		VerifyRational(CRational(1, 2) += CRational(0, 6), 1, 2);
	}

	BOOST_AUTO_TEST_CASE(has_subtracting_assignment_operator)
	{
		VerifyRational(CRational(1, 2) -= CRational(1, 6), 1, 3);
		VerifyRational(CRational(1, 2) -= 1, -1, 2);
		VerifyRational(CRational(1, 2) -= CRational(0, 6), 1, 2);
	}

	BOOST_AUTO_TEST_CASE(has_binary_multiplication_operation)
	{
		VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
		VerifyRational(CRational(1, 2) * (-3), -3, 2);
		VerifyRational(7 * CRational(2, 3), 14, 3);
	}

	BOOST_AUTO_TEST_CASE(has_division_operation)
	{
		VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) / 5, 1, 10);
		VerifyRational(7 / CRational(2, 3), 21, 2);
		BOOST_REQUIRE_THROW(CRational(2, 3) / 0, std::invalid_argument);
		BOOST_REQUIRE_THROW(CRational(2, 3) / CRational(0, 1), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()

