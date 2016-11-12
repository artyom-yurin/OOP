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
}

CVariable::CVariable(double value)
{
	m_value = value;
}
