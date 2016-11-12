#include "stdafx.h"
#include "Variable.h"

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
	for (std::shared_ptr<CFunction> function : functions)
	{
		function->Refresh();
	}
}

void CVariable::AddFunction(std::shared_ptr<CFunction> & pFunction)
{
}

CVariable::CVariable(double value)
{
	m_value = value;
}
