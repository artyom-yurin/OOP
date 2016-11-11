#include "stdafx.h"
#include "Function.h"

CFunction::CFunction(const std::shared_ptr<CIndex> & index)
{
	m_value = index->GetResult();
	m_firstIndex = index;
}

CFunction::CFunction(std::shared_ptr<CIndex> firstIndex, Sign sign, std::shared_ptr<CIndex> secondIndex)
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

void CFunction::Refresh()
{
	if (m_secondIndex == nullptr)
	{
		m_value = m_firstIndex->GetResult();
		return;
	}
	if (m_sign == Sign::plus)
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
