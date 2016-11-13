#pragma once
#include "Variable.h"
#include "Function.h"

class CCalc
{
public:
	CCalc() = default;

	~CCalc() = default;

	void Var(std::string name);

	void Let(std::string name, double value);

	std::shared_ptr<CIndex> GetIndex(std::string name);

	std::map<std::string, std::shared_ptr<CVariable>> GetVariables() const;

	std::map<std::string, std::shared_ptr<CFunction>> GetFunctions() const;

private:
	std::map<std::string, std::shared_ptr<CVariable>> m_variables;
	std::map<std::string, std::shared_ptr<CFunction>> m_functions;
};

