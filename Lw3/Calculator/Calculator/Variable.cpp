#include "stdafx.h"
#include "Variable.h"
#include "Function.h"

std::shared_ptr<CVariable> CVariable::Create()
{
	return std::shared_ptr<CVariable>(new CVariable());
}

std::shared_ptr<CVariable> CVariable::Create(double value)
{
	return std::shared_ptr<CVariable>(new CVariable(value));
}

void CVariable::SetValue(double value)
{
	m_value = value;
	for (std::shared_ptr<CFunction> function : m_dependentFunctions)
	{
		function->Refresh();
	}
}

void CVariable::AddDependentFunction(std::shared_ptr<CFunction> pFunction)
{
	m_dependentFunctions.push_back(pFunction);
}

CVariable::CVariable(double value)
{
	m_value = value;
}
