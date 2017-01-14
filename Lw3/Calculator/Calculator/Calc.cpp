#include "stdafx.h"
#include "Calc.h"

bool CCalc::isValidName(std::string const & name) const
{
	return std::regex_match(name, std::regex("[A-Za-z]\\w*"));
}

std::vector<std::shared_ptr<CVariable>> MergeVector(std::vector<std::shared_ptr<CVariable>> const & firstVector, std::vector<std::shared_ptr<CVariable>> const & secondVector)
{
	std::vector<std::shared_ptr<CVariable>> result = firstVector;

	std::copy(secondVector.begin(), secondVector.end(), std::back_inserter(result));

	result.erase(
		std::unique(result.begin(), result.end()),
		result.end());

	return result;
}

void CCalc::Var(std::string const & name)
{
	if (m_variables.find(name) == m_variables.end() && m_functions.find(name) == m_functions.end())
	{
		m_variables[name] = CVariable::Create();
	}
}

void CCalc::Let(std::string const & name, double value)
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

void CCalc::Let(std::string const & name, std::string const & indexName)
{
	if (m_functions.find(name) == m_functions.end())
	{
		if (m_variables.find(name) != m_variables.end())
		{	
			if (m_variables.find(indexName) != m_variables.end())
			{
				m_variables[name]->SetValue(m_variables[indexName]->GetResult());
			}
			else if (m_functions.find(indexName) != m_functions.end())
			{
				m_variables[name]->SetValue(m_functions[indexName]->GetResult());
			}
		}
		else
		{
			if (m_variables.find(indexName) != m_variables.end())
			{
				m_variables[name] = CVariable::Create(m_variables[indexName]->GetResult());
			}
			else if (m_functions.find(indexName) != m_functions.end())
			{
				m_variables[name] = CVariable::Create(m_functions[indexName]->GetResult());
			}
		}
	}
}
//TODO: Find memory leaks down
void CCalc::Fn(std::string const & name, std::string const & indexName)
{
	if (m_functions.find(name) == m_functions.end() && m_variables.find(name) == m_variables.end())
	{
		if (m_variables.find(indexName) != m_variables.end())
		{
			m_functions[name] = CFunction::Create(m_variables[indexName]);
			m_variables[indexName]->AddDependentFunction(m_functions[name]);
			m_functions[name]->AddDependentVariable(m_variables[indexName]);
		} 
		else if (m_functions.find(indexName) != m_functions.end())
		{
			m_functions[name] = CFunction::Create(m_functions[indexName]);
			for (std::shared_ptr<CVariable> variable : m_functions[indexName]->GetDependentVariables())
			{
				variable->AddDependentFunction(m_functions[name]);
			}
			m_functions[name]->AddDependentVariables(m_functions[indexName]->GetDependentVariables());
		}
	}
}

void CCalc::Fn(std::string const & name, std::string const & firstIndexName, Sign sign, std::string const & secondIndexName)
{
	if (m_functions.find(name) == m_functions.end() && m_variables.find(name) == m_variables.end())
	{
		if (m_variables.find(firstIndexName) != m_variables.end())
		{
			if (m_variables.find(secondIndexName) != m_variables.end())
			{
				m_functions[name] = CFunction::Create(m_variables[firstIndexName], sign, m_variables[secondIndexName]);
				m_variables[firstIndexName]->AddDependentFunction(m_functions[name]);
				m_functions[name]->AddDependentVariable(m_variables[firstIndexName]);
				if (firstIndexName != secondIndexName)
				{
					m_variables[secondIndexName]->AddDependentFunction(m_functions[name]);
					m_functions[name]->AddDependentVariable(m_variables[secondIndexName]);
				}
			}
			else if (m_functions.find(secondIndexName) != m_functions.end())
			{
				m_functions[name] = CFunction::Create(m_variables[firstIndexName], sign, m_functions[secondIndexName]);
				std::vector<std::shared_ptr<CVariable>> dependentVariables = MergeVector(m_functions[secondIndexName]->GetDependentVariables(), std::vector<std::shared_ptr<CVariable>> {m_variables[firstIndexName]});
				for (std::shared_ptr<CVariable> variable : dependentVariables)
				{
					variable->AddDependentFunction(m_functions[name]);
				}
				m_functions[name]->AddDependentVariables(dependentVariables);
			}
		}
		else if (m_functions.find(firstIndexName) != m_functions.end())
		{
			if (m_variables.find(secondIndexName) != m_variables.end())
			{
				m_functions[name] = CFunction::Create(m_functions[firstIndexName], sign, m_variables[secondIndexName]);
				std::vector<std::shared_ptr<CVariable>> dependentVariables = MergeVector(m_functions[firstIndexName]->GetDependentVariables(), std::vector<std::shared_ptr<CVariable>> {m_variables[secondIndexName]});
				for (std::shared_ptr<CVariable> variable : dependentVariables)
				{
					variable->AddDependentFunction(m_functions[name]);
				}
				m_functions[name]->AddDependentVariables(dependentVariables);
			}
			else if (m_functions.find(secondIndexName) != m_functions.end())
			{
				m_functions[name] = CFunction::Create(m_functions[firstIndexName], sign, m_functions[secondIndexName]);
				std::vector<std::shared_ptr<CVariable>> dependentVariables = MergeVector(m_functions[firstIndexName]->GetDependentVariables(), m_functions[secondIndexName]->GetDependentVariables());
				for (std::shared_ptr<CVariable> variable : dependentVariables)
				{
					variable->AddDependentFunction(m_functions[name]);
				}
				m_functions[name]->AddDependentVariables(dependentVariables);
			}
		}
	}
}
//TODO: Find memory leaks up
std::shared_ptr<CIndex> CCalc::GetIndex(std::string const & name)
{
	if (m_functions.find(name) != m_functions.end())
	{
		return m_functions[name];
	}
	else if (m_variables.find(name) != m_variables.end())
	{
		return m_variables[name];
	}
	return nullptr;
}

void CCalc::Print(std::ostream & output, std::string const & name)
{
	auto index = GetIndex(name);
	if (index != nullptr)
	{
		output << std::fixed;
		output << std::setprecision(2);
		output << name << ":";
		double value = index->GetResult();
		if (std::isnan(value))
		{
			output << "nan";
		}
		else
		{
			output << value;
		}
	}
}

void CCalc::PrintVars(std::ostream & output)
{
	output << std::fixed
		<< std::setprecision(2);
	for (auto variable : m_variables)
	{
		output << variable.first << ":";
		double value = variable.second->GetResult();
		if (std::isnan(value))
		{
			output << "nan";
		}
		else
		{
			output << value;
		}
		output << std::endl;
	}
}

void CCalc::PrintFns(std::ostream & output)
{
	output << std::fixed
		<< std::setprecision(2);
	for (auto function : m_functions)
	{
		output << function.first << ":";
		double value = function.second->GetResult();
		if (std::isnan(value))
		{
			output << "nan";
		}
		else
		{
			output << value;
		}
		output << std::endl;
	}
}

std::map<std::string, std::shared_ptr<CVariable>> CCalc::GetVariables() const
{
	return m_variables;
}

std::map<std::string, std::shared_ptr<CFunction>> CCalc::GetFunctions() const
{
	return m_functions;
}
