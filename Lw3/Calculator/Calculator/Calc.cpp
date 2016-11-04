#include "stdafx.h"

#include "Calc.h"

bool CCalc::Var(std::string name)
{
	if (m_variables.find(name) == m_variables.end())
	{
		m_variables[name] = 0;
		return true;
	}
	std::cout << "Variable \""<< name << "\" have declarated\n";
	return false;
}

std::map<std::string, double> CCalc::GetVariables() const
{
	return m_variables;
}

bool CCalc::Let(std::string firstName, std::string secondName)
{
	if (m_variables.find(firstName) != m_variables.end())
	{
		if (m_variables.find(secondName) != m_variables.end())
		{
			m_variables[firstName] = m_variables[secondName];
			return true;
		}
		std::cout << "Variable \"" << secondName << "\" have not declarated\n";
		return false;
	}
	std::cout << "Variable \"" << firstName << "\" have not declarated\n";
	return false;
}

bool CCalc::Let(std::string name, double value)
{
	if (m_variables.find(name) != m_variables.end())
	{
		m_variables[name] = value;
		return true;
	}
	std::cout << "Variable\"" << name << "\"have not declarated\n";
	return false;
}


