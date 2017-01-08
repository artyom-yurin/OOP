#include "stdafx.h"
#include "StringList.h"
#include <cassert>

using namespace std;

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::Append(const std::string & data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node *newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

void CStringList::push_front(const std::string & data)
{
	if (empty())
	{
		Append(data);
	}
	auto secondNode = move(m_firstNode);
	m_firstNode = make_unique<Node>(data, nullptr, move(secondNode));
	++m_size;
}

bool CStringList::empty() const
{
	return !m_size;
}

void CStringList::clear()
{
	m_firstNode = nullptr;
	m_lastNode = nullptr;
	m_size = 0;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	if (empty())
	{
		begin();
	}
	return CIterator(m_lastNode->next.get());
}

const CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_firstNode.get());
}

const CStringList::CIterator CStringList::cend() const
{
	if (empty())
	{
		cbegin();
	}
	return CIterator(m_lastNode->next.get());
}

std::string & CStringList::GetBackElement()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string const & CStringList::GetBackElement() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string & CStringList::GetFrontElement()
{
	assert(m_firstNode);
	return m_firstNode->data;
}

std::string const & CStringList::GetFrontElement() const
{
	assert(m_firstNode);
	return m_firstNode->data;
}

CStringList::CIterator::CIterator(Node * node)
	:m_node(node)
{
}

std::string & CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	m_node = m_node->prev;
	return *this;
}
