#include "stdafx.h"
#include "Function.h"
#include "Variable.h"

CFunction::CFunction(std::shared_ptr<CIndex> const & index)
{
	m_value = index->GetResult();
	m_firstIndex = index;
}

CFunction::CFunction(std::shared_ptr<CIndex> const & firstIndex, Sign sign, std::shared_ptr<CIndex> const & secondIndex)
{
	m_sign = sign;
	if (m_sign == Sign::plus)
	{
		m_value = firstIndex->GetResult() + secondIndex->GetResult();
	}
	else if (m_sign == Sign::minus)
	{
		m_value = firstIndex->GetResult() - secondIndex->GetResult();
	}
	else if (m_sign == Sign::factor)
	{
		m_value = firstIndex->GetResult() * secondIndex->GetResult();
	}
	else if (m_sign == Sign::divider)
	{
		if (secondIndex->GetResult() != 0)
		{
			m_value = firstIndex->GetResult() / secondIndex->GetResult();
		}
		else
		{
			m_value = firstIndex->GetResult();
		}
	}
	m_firstIndex = firstIndex;
	m_secondIndex = secondIndex;
}

std::shared_ptr<CFunction> CFunction::Create(std::shared_ptr<CIndex> const & index)
{
	return std::make_shared<CFunction>(index);
}

std::shared_ptr<CFunction> CFunction::Create(std::shared_ptr<CIndex> const & firstIndex, Sign sign, std::shared_ptr<CIndex> const & secondIndex)
{
	return std::make_shared<CFunction>(firstIndex, sign, secondIndex);
}

void CFunction::AddDependentVariables(std::vector<std::shared_ptr<CVariable>> const & dependentVariables)
{
	m_dependentVariables = dependentVariables;
}

void CFunction::AddDependentVariable(std::shared_ptr<CVariable> const & dependentVariable)
{
	m_dependentVariables.push_back(dependentVariable);
}

std::vector<std::shared_ptr<CVariable>> & CFunction::GetDependentVariables()
{
	return m_dependentVariables;
}

void CFunction::Refresh()
{
	if (m_secondIndex == nullptr)
	{
		m_value = m_firstIndex->GetResult();
	}
	else if (m_sign == Sign::plus)
	{
		m_value = m_firstIndex->GetResult() + m_secondIndex->GetResult();
	}
	else if (m_sign == Sign::minus)
	{
		m_value = m_firstIndex->GetResult() - m_secondIndex->GetResult();
	}
	else if (m_sign == Sign::factor)
	{
		m_value = m_firstIndex->GetResult() * m_secondIndex->GetResult();
	}
	else if (m_sign == Sign::divider)
	{
		if (m_secondIndex->GetResult() != 0)
		{
			m_value = m_firstIndex->GetResult() / m_secondIndex->GetResult();
		}
		else
		{
			m_value = m_firstIndex->GetResult();
		}
	}
}
