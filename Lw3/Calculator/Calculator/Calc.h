#pragma once

class CCalc
{
public:
	CCalc() = default;
	~CCalc() = default;

private:
	std::map <std::string, double> m_values;
	std::map <std::string, double> m_functions;
};

