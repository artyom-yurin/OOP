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

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

const CRational CRational::operator+=(const CRational & summand)
{
	if (summand.GetNumerator())
	{
		int numerator = GetNumerator() * summand.GetDenominator() + summand.GetNumerator() * GetDenominator();
		int denominator = GetDenominator() * summand.GetDenominator();
		Assign(numerator, denominator);
	}
	return *this;
}

const CRational CRational::operator-=(const CRational & subtrahend)
{
	if (subtrahend.GetNumerator())
	{
		int numerator = GetNumerator() * subtrahend.GetDenominator() - subtrahend.GetNumerator() * GetDenominator();
		int denominator = GetDenominator() * subtrahend.GetDenominator();
		Assign(numerator, denominator);
	}
	return *this;
}

const CRational CRational::operator*=(const CRational & factor)
{
	int numerator = GetNumerator() * factor.GetNumerator();
	int denominator = GetDenominator() * factor.GetDenominator();
	Assign(numerator, denominator);
	return *this;
}

const CRational CRational::operator/=(const CRational & divider)
{
	int numerator = GetNumerator() * divider.GetDenominator();
	int denominator = GetDenominator() * divider.GetNumerator();
	Assign(numerator, denominator);
	return *this;
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

const CRational operator+(const CRational & lhs, const CRational & rhs)
{
	int numerator = lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator();
	int denominator = lhs.GetDenominator() * rhs.GetDenominator();
	return CRational(numerator, denominator);
}

const CRational operator-(const CRational & lhs, const CRational & rhs)
{
	int numerator = lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator();
	int denominator = lhs.GetDenominator() * rhs.GetDenominator();
	return CRational(numerator, denominator);
}

const CRational operator*(const CRational & lhs, const CRational & rhs)
{
	int numerator = lhs.GetNumerator() * rhs.GetNumerator();
	int denominator = lhs.GetDenominator() * rhs.GetDenominator();
	return CRational(numerator, denominator);
}

const CRational operator/(const CRational & lhs, const CRational & rhs)
{
	int numerator = lhs.GetNumerator() * rhs.GetDenominator();
	int denominator = lhs.GetDenominator() * rhs.GetNumerator();
	return CRational(numerator, denominator);
}

const bool operator==(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() == rhs.GetNumerator() &&
		lhs.GetDenominator() == rhs.GetDenominator());
}

const bool operator<(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator());
}

const bool operator<=(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() <= rhs.GetNumerator() * lhs.GetDenominator());
}

const bool operator>=(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() >= rhs.GetNumerator() * lhs.GetDenominator());
}

const bool operator>(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() > rhs.GetNumerator() * lhs.GetDenominator());
}

std::ostream & operator<<(std::ostream & output, const CRational & value)
{
	output << value.GetNumerator() << "/" << value.GetDenominator();
	return output;
}

std::istream & operator>>(std::istream & stream, CRational & value)
{
	int numerator = 0;
	int	denominator = 1;
	if (
		(stream >> numerator) &&
		(stream.get() == '/') && 
		(stream >> denominator)
		)
	{
		value = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
	}

	return stream;
}



const bool operator!=(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() != rhs.GetNumerator() ||
		lhs.GetDenominator() != rhs.GetDenominator());
}
