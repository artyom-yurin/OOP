#include "stdafx.h"

#include "Calc.h"

#include <string>

bool CCalc::Var(std::string name)
{
	if (m_variables.find(name) == m_variables.end())
	{
		m_variables[name] = 0;
		return true;
	}
	return false;
}

std::map<std::string, double> CCalc::GetVariables() const
{
	return m_variables;
}


