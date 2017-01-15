#pragma once
#include "Variable.h"
#include "Function.h"

class CCalc
{
public:
	CCalc() = default;

	~CCalc() = default;

	bool isValidName(std::string const & name) const;

	void Var(std::string const & name);

	void Let(std::string const & name, double value);

	void Let(std::string const & name, std::string const & indexName);

	void Fn(std::string const & name, std::string const & indexName);

	void Fn(std::string const & name, std::string const & firstIndexName, Sign sign, std::string const & secondIndexName);

	void Print(std::ostream & output, std::string const & name);

	void PrintVars(std::ostream & output);

	void PrintFns(std::ostream & output);

	std::shared_ptr<CIndex> GetIndex(std::string const & name);

	std::map<std::string, std::shared_ptr<CVariable>> GetVariables() const;

	std::map<std::string, std::shared_ptr<CFunction>> GetFunctions() const;

private:
	std::vector<std::shared_ptr<CVariable>> GetDependentVariables(std::string const & indexName);

	std::map<std::string, std::shared_ptr<CVariable>> m_variables;
	std::map<std::string, std::shared_ptr<CFunction>> m_functions;
};

