#include "stdafx.h"
#include "StringList.h"

void ClearLinks(std::shared_ptr<Node> const & firstNode)
{
	auto currentNode = firstNode;
	auto nextNode = firstNode->next;
	while (nextNode != nullptr)
	{
		currentNode->next = nullptr;
		currentNode->prev = nullptr;
		currentNode = nextNode;
		nextNode = currentNode->next;
	}
}

CStringList::CStringList()
{
	clear();
}

CStringList::CStringList(const CStringList & list)
{
	CStringList tempList;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		tempList.Append(*it);
	}
	std::swap(tempList, *this);
}

CStringList::CStringList(CStringList && list)
{
	std::swap(m_firstNode, list.m_firstNode);
	std::swap(m_lastNode, list.m_lastNode);
	std::swap(m_size, list.m_size);
}

CStringList::~CStringList()
{
	ClearLinks(m_firstNode);
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::Append(const std::string & data)
{
	auto newNode = std::make_shared<Node>(data, m_lastNode->prev, m_lastNode);
	m_lastNode->prev->next = newNode;
	m_lastNode->prev = newNode;
	++m_size;
}

void CStringList::push_front(const std::string & data)
{
	auto newNode = std::make_shared<Node>(data, m_firstNode, m_firstNode->next);
	m_firstNode->next->prev = newNode;
	m_firstNode->next = newNode;
	++m_size;
}

bool CStringList::empty() const
{
	return !m_size;
}

void CStringList::clear()
{
	ClearLinks(m_firstNode);
	m_firstNode->next = m_lastNode;
	m_lastNode->prev = m_firstNode;
	m_size = 0;
}

CStringList & CStringList::operator=(const CStringList & list)
{
	if (&list != this)
	{
		CStringList tempList(list);
		std::swap(tempList, *this);
	}
	return *this;
}

CStringList & CStringList::operator=(CStringList && list)
{
	if (&list != this)
	{
		std::swap(m_firstNode, list.m_firstNode);
		std::swap(m_lastNode, list.m_lastNode);
		std::swap(m_size, list.m_size);
	}
	return *this;
}

CStringList::IteratorType CStringList::begin()
{
	return CIterator<std::string>(m_firstNode->next);
}

CStringList::IteratorType CStringList::end()
{
	return CIterator<std::string>(m_lastNode);
}

CStringList::ConstIteratorType CStringList::begin() const
{
	return CIterator<const std::string>(m_firstNode->next);
}

CStringList::ConstIteratorType CStringList::end() const
{
	return CIterator<const std::string>(m_lastNode);
}

CStringList::ConstIteratorType CStringList::cbegin() const
{
	return CIterator<const std::string>(m_firstNode->next);
}

CStringList::ConstIteratorType CStringList::cend() const
{
	return CIterator<const std::string>(m_lastNode);
}

CStringList::ReverseIteratorType CStringList::rbegin()
{
	return ReverseIteratorType(end());
}

CStringList::ReverseIteratorType CStringList::rend()
{
	return ReverseIteratorType(begin());
}

CStringList::ConstReverseIteratorType CStringList::rbegin() const
{
	return ConstReverseIteratorType(end());
}

CStringList::ConstReverseIteratorType CStringList::rend() const
{
	return ConstReverseIteratorType(begin());
}

CStringList::ConstReverseIteratorType CStringList::crbegin() const
{
	return ConstReverseIteratorType(cend());
}

CStringList::ConstReverseIteratorType CStringList::crend() const
{
	return ConstReverseIteratorType(cbegin());
}

std::string & CStringList::GetBackElement()
{
	if (empty())
	{
		throw std::logic_error("list is empty");
	}
	return m_lastNode->prev->data;
}

std::string const & CStringList::GetBackElement() const
{
	if (empty())
	{
		throw std::logic_error("list is empty");
	}
	return m_lastNode->prev->data;
}

std::string & CStringList::GetFrontElement()
{
	if (empty())
	{
		throw std::logic_error("list is empty");
	}
	return m_firstNode->next->data;
}

std::string const & CStringList::GetFrontElement() const
{
	if (empty())
	{
		throw std::logic_error("list is empty");
	}
	return m_firstNode->next->data;
}

bool operator==(const CStringList & lhs, const CStringList & rhs)
{
	if (&lhs == &rhs)
	{
		return true;
	}
	if (lhs.GetSize() == rhs.GetSize())
	{
		auto rhsIt = rhs.begin();
		for (auto lhsIt = lhs.begin(); lhsIt != lhs.end(); ++lhsIt, ++rhsIt)
		{
			if (*lhsIt != *rhsIt)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool operator!=(const CStringList & lhs, const CStringList & rhs)
{
	return !(lhs == rhs);
}
