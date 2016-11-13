#include "stdafx.h"
#include "Calc.h"

void CCalc::Var(std::string name)
{
	if (m_variables.find(name) == m_variables.end() && m_functions.find(name) == m_functions.end())
	{
		m_variables[name] = CVariable::Create();
	}
}

void CCalc::Let(std::string name, double value)
{
	if (m_functions.find(name) == m_functions.end())
	{
		if (m_variables.find(name) != m_variables.end())
		{
			m_variables[name]->SetValue(value);
		}
		else
		{
			m_variables[name] = CVariable::Create(value);
		}
	}
}

std::shared_ptr<CIndex> CCalc::GetIndex(std::string name)
{
	if (m_functions.find(name) != m_functions.end())
	{
		return m_functions[name];
	}
	else if (m_functions.find(name) != m_functions.end())
	{
		return m_variables[name];
	}
	return nullptr;
}

std::map<std::string, std::shared_ptr<CVariable>> CCalc::GetVariables() const
{
	return m_variables;
}

std::map<std::string, std::shared_ptr<CFunction>> CCalc::GetFunctions() const
{
	return m_functions;
}
