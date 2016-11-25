#pragma once
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

	const CRational operator+() const;

	const CRational operator-() const;

private:
	int m_numerator;

	int m_denominator;

	void Assign(int numerator, int denominator);

	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);