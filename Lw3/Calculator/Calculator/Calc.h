#pragma once
enum class Sign
{
	plus,
	minus,
	factor,
	divider
};
class CCalc
{
public:
	CCalc() = default;

	~CCalc() = default;

	bool Var(std::string name);

	std::map <std::string, double> GetVariables() const;

	bool Let(std::string firstName, std::string secondName);

	bool Let(std::string name, double value);

	bool Fn(std::string functionName, std::string name);

	bool Fn(std::string functionName, std::string firstName, Sign sign, std::string secondName);

	double Get(std::string name) const;

	std::map <std::string, double*> GetFunctions() const;

private:
	std::map <std::string, double> m_variables;
	std::map <std::string, double*> m_functions;
};

