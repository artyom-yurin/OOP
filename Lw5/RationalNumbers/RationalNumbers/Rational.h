#pragma once

#include <iostream>

class CRational
{
public:
	CRational();

	CRational(int value);

	CRational(int numerator, int denominator);

	~CRational() = default;

	int GetNumerator() const;

	int GetDenominator() const;

	double ToDouble() const;

	std::pair<int, CRational> ToCompoundFraction()const;

	const CRational operator+() const;

	const CRational operator-() const;

	const CRational operator+=(const CRational & summand);

	const CRational operator-=(const CRational & subtrahend);

	const CRational operator*=(const CRational & factor);

	const CRational operator/=(const CRational & divider);

private:
	int m_numerator;

	int m_denominator;

	void Assign(int numerator, int denominator);

	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);

const CRational operator+(const CRational & lhs, const CRational & rhs);
const CRational operator-(const CRational & lhs, const CRational & rhs);
const CRational operator*(const CRational & lhs, const CRational & rhs);
const CRational operator/(const CRational & lhs, const CRational & rhs);

const bool operator!=(const CRational & lhs, const CRational & rhs);
const bool operator==(const CRational & lhs, const CRational & rhs);

const bool operator<(const CRational & lhs, const CRational & rhs);
const bool operator<=(const CRational & lhs, const CRational & rhs);
const bool operator>=(const CRational & lhs, const CRational & rhs);
const bool operator>(const CRational & lhs, const CRational & rhs);

std::ostream & operator<<(std::ostream & stream, const CRational & value);
std::istream & operator>>(std::istream & stream, CRational & value);