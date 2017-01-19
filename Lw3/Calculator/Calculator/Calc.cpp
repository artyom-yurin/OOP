#include "stdafx.h"
#include "Calc.h"

CCalc::~CCalc()
{
	for (auto & function : m_functions)
	{
		function.second->Clear();
	}
}

bool CCalc::isValidName(std::string const & name) const
{
	return std::regex_match(name, std::regex("[A-Za-z]\\w*"));
}

std::vector<std::shared_ptr<CVariable>> CCalc::GetDependentVariables(std::string const & indexName)
{
	std::vector<std::shared_ptr<CVariable>> dependVariables;
	auto variable = m_variables.find(indexName);
	if (variable != m_variables.cend())
	{
		dependVariables.push_back(variable->second);
	}
	else
	{
		auto variables = m_functions.find(indexName)->second->GetDependentVariables();
		dependVariables.insert(dependVariables.cend(), variables.cbegin(), variables.cend());
	}
	return dependVariables;
}

std::vector<std::shared_ptr<CVariable>> MergeVector(std::vector<std::shared_ptr<CVariable>> const & firstVector, std::vector<std::shared_ptr<CVariable>> const & secondVector)
{
	std::vector<std::shared_ptr<CVariable>> result(firstVector);
	for (auto element : secondVector)
	{
		if (!std::any_of(result.cbegin(), result.cend(), [element](std::shared_ptr<CVariable> el) { return el == element; }))
		{
			result.insert(result.cend(), element);
		}
	}
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

void CCalc::Fn(std::string const & name, std::string const & indexName)
{
	if (m_functions.find(name) == m_functions.end() && m_variables.find(name) == m_variables.end())
	{
		auto index = GetIndex(indexName);
		if (index != nullptr)
		{
			std::vector<std::shared_ptr<CVariable>> dependentVariables = GetDependentVariables(indexName);
			m_functions[name] = CFunction::Create(index);
			for (std::shared_ptr<CVariable> variable : dependentVariables)
			{
				variable->AddDependentFunction(m_functions[name]);
			}
			m_functions[name]->AddDependentVariables(dependentVariables);
		}
		else
		{
			throw std::invalid_argument("Element " + indexName + " does not exist");
		}
	}
	else
	{
		throw std::invalid_argument("Name " + name + " busy");
	}
}

void CCalc::Fn(std::string const & name, std::string const & firstIndexName, Sign sign, std::string const & secondIndexName)
{
	if (m_functions.find(name) == m_functions.end() && m_variables.find(name) == m_variables.end())
	{
		auto firstIndex = GetIndex(firstIndexName);
		if (firstIndex != nullptr)
		{
			auto secondIndex = GetIndex(secondIndexName);
			if (secondIndex != nullptr)
			{
				std::vector<std::shared_ptr<CVariable>> dependentVariables = GetDependentVariables(firstIndexName);
				dependentVariables = MergeVector(dependentVariables, GetDependentVariables(secondIndexName));
				m_functions[name] = CFunction::Create(firstIndex, sign, secondIndex);
				for (std::shared_ptr<CVariable> variable : dependentVariables)
				{
					variable->AddDependentFunction(m_functions[name]);
				}
				m_functions[name]->AddDependentVariables(dependentVariables);
			}
			else
			{
				throw std::invalid_argument("Element " + secondIndexName + " does not exist");
			}
		}
		else
		{
			throw std::invalid_argument("Element " + firstIndexName + " does not exist");
		}
	}
	else
	{
		throw std::invalid_argument("Name " + name + " busy");
	}
}

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
