#include "stdafx.h"
#include "Rational.h"
#include <stdexcept>

CRational::CRational()
{
	Assign(0, 1);
}

CRational::CRational(int value)
{
	Assign(value, 1);
}

CRational::CRational(int numerator, int denominator)
{
	Assign(numerator, denominator);
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Assign(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
	m_numerator = numerator;
	m_denominator = denominator;
	Normalize();
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}
