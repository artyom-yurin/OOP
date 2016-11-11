#include "stdafx.h"
#include "Variable.h"

CVariable::CVariable(double & value)
{
	m_value = value;
}

void CVariable::SetValue(double & value)
{
	m_value = value;
}