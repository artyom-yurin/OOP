#include "stdafx.h"
#include "Variable.h"
#include "Function.h"

std::shared_ptr<CVariable> CVariable::Create()
{
	return std::make_shared<CVariable>(NAN);
}

std::shared_ptr<CVariable> CVariable::Create(double value)
{
	return std::make_shared<CVariable>(value);
}

void CVariable::SetValue(double value)
{
	if (m_value != value)
	{
		m_value = value;
		for (std::weak_ptr<CFunction> function : m_dependentFunctions)
		{
			function.lock()->Refresh();
		}
	}	
}

void CVariable::AddDependentFunction(std::shared_ptr<CFunction> const & pFunction)
{
	m_dependentFunctions.push_back(pFunction);
}

CVariable::CVariable(double value)
{
	m_value = value;
}
