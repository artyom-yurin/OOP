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
	if (list != *this)
	{
		CStringList tempList(list);
		std::swap(tempList, *this);
	}
	return *this;
}

CStringList & CStringList::operator=(CStringList && list)
{
	std::swap(m_firstNode, list.m_firstNode);
	std::swap(m_lastNode, list.m_lastNode);
	std::swap(m_size, list.m_size);
	return *this;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode->next);
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::begin() const
{
	return CIterator(m_firstNode->next);
}

const CStringList::CIterator CStringList::end() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_firstNode->next);
}

const CStringList::CIterator CStringList::cend() const
{
	return CIterator(m_lastNode);
}

CStringList::CReverseIterator CStringList::rbegin()
{
	return CReverseIterator(end());
}

CStringList::CReverseIterator CStringList::rend()
{
	return CReverseIterator(begin());
}

const CStringList::CReverseIterator CStringList::rbegin() const
{
	return CReverseIterator(end());
}

const CStringList::CReverseIterator CStringList::rend() const
{
	return CReverseIterator(begin());
}

const CStringList::CReverseIterator CStringList::crbegin() const
{
	return CReverseIterator(cend());
}

const CStringList::CReverseIterator CStringList::crend() const
{
	return CReverseIterator(cbegin());
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

void CStringList::insert(const CIterator & it, const std::string & data)
{
	auto newNode = std::make_shared<Node>(data, it.m_node->prev, it.m_node);
	it.m_node->prev->next = newNode;
	it.m_node->prev = newNode;
	++m_size;
}

void CStringList::erase(const CIterator & it)
{
	if (!it.m_node->prev || !it.m_node->next)
	{
		throw std::logic_error("can not deleted the element of end or rend iterator");
	}
	it.m_node->next->prev = it.m_node->prev;
	it.m_node->prev->next = it.m_node->next;
	--m_size;
}

CStringList::CIterator::CIterator(std::shared_ptr<Node> const & node)
	:m_node(node)
{
}

std::string & CStringList::CIterator::operator*() const
{
	if (!m_node->prev || !m_node->next)
	{
		throw std::logic_error("can not take the value of end or rend iterator");
	}
	return m_node->data;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	if (!m_node->next)
	{
		throw std::logic_error("reached the end of the list");
	}
	m_node = m_node->next;
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator++(int)
{
	auto copy = *this;
	++*this;
	return copy;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	if (!m_node->prev)
	{
		throw std::logic_error("reached the begin of the list");
	}
	m_node = m_node->prev;
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator--(int)
{
	auto copy = *this;
	--*this;
	return copy;
}

bool CStringList::CIterator::operator==(const CStringList::CIterator & it) const
{
	return (m_node == it.m_node);
}

bool CStringList::CIterator::operator!=(const CStringList::CIterator & it) const
{
	return (m_node != it.m_node);
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
