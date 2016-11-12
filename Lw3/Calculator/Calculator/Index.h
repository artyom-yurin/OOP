#pragma once

class CIndex
{
public:
	CIndex() = default;

	virtual ~CIndex() = default;

	double GetResult() const;

protected:

	double m_value = 0.0;
};
