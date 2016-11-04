#pragma once

class CCalc
{
public:
	CCalc() = default;

	~CCalc() = default;

	bool Var(std::string name);

	std::map <std::string, double> GetVariables() const;

private:
	std::map <std::string, double> m_variables;
	std::map <std::string, double> m_functions;
};

