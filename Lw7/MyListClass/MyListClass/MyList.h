#pragma once

#include <string>
#include <memory>
#include <iterator>

template <typename T>
struct Node
{
	Node() {};
	Node(T const & data, std::shared_ptr<Node<T>> const & prev, std::shared_ptr<Node<T>> const & next)
		: data(std::make_unique<T>(data)), prev(prev), next(next)
	{
	}
	std::unique_ptr<T> data = nullptr;
	std::shared_ptr<Node<T>> prev = nullptr;
	std::shared_ptr<Node<T>> next = nullptr;	
};

template <typename T>
class CMyList
{
public:
	CMyList() 
	{
		clear();
	}

	CMyList(const CMyList & list)
	{
		CMyList tempList;
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			tempList.Append(*it);
		}
		std::swap(tempList, *this);
	}

	CMyList(CMyList && list)
	{
		std::swap(m_firstNode, list.m_firstNode);
		std::swap(m_lastNode, list.m_lastNode);
		std::swap(m_size, list.m_size);
	}

	~CMyList()
	{
		ClearLinks(m_firstNode);
	}

	size_t GetSize()const
	{
		return m_size;
	}

	void Append(const T& data)
	{
		auto newNode = std::make_shared<Node<T>>(data, m_lastNode->prev, m_lastNode);
		m_lastNode->prev->next = newNode;
		m_lastNode->prev = newNode;
		++m_size;
	}

	void push_front(const T& data)
	{
		auto newNode = std::make_shared<Node<T>>(data, m_firstNode, m_firstNode->next);
		m_firstNode->next->prev = newNode;
		m_firstNode->next = newNode;
		++m_size;
	}

	bool empty()const
	{
		return !m_size;
	}

	void clear()
	{
		ClearLinks(m_firstNode);
		m_firstNode->next = m_lastNode;
		m_lastNode->prev = m_firstNode;
		m_size = 0;
	}

	CMyList & operator=(const CMyList & list)
	{
		if (&list != this)
		{
			CMyList tempList(list);
			std::swap(tempList, *this);
		}
		return *this;
	}

	CMyList & operator=(CMyList && list)
	{
		if (&list != this)
		{
			std::swap(m_firstNode, list.m_firstNode);
			std::swap(m_lastNode, list.m_lastNode);
			std::swap(m_size, list.m_size);
		}
		return *this;
	}

	template <class IterT>
	class CIterator
	{
		friend CMyList;
		CIterator(std::shared_ptr<Node<IterT>> const & node)
			:m_node(node)
		{
		}
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef IterT value_type;
		typedef ptrdiff_t difference_type;
		typedef IterT* pointer;
		typedef IterT& reference;
		IterT & operator*()const
		{
			if (!m_node->prev || !m_node->next)
			{
				throw std::logic_error("can not take the value of end or rend iterator");
			}
			return *m_node->data;
		}

		CIterator & operator++()
		{
			if (!m_node->next)
			{
				throw std::logic_error("reached the end of the list");
			}
			m_node = m_node->next;
			return *this;
		}

		CIterator operator++(int)
		{
			auto copy = *this;
			++*this;
			return copy;
		}

		CIterator & operator--()
		{
			if (!m_node->prev)
			{
				throw std::logic_error("reached the begin of the list");
			}
			m_node = m_node->prev;
			return *this;
		}

		CIterator operator--(int)
		{
			auto copy = *this;
			--*this;
			return copy;
		}

		bool operator==(const CIterator & it) const
		{
			return (m_node == it.m_node);
		}

		bool operator!=(const CIterator & it) const
		{
			return (m_node != it.m_node);
		}

	private:
		Node<IterT> * CIterator::operator->() const
		{
			if (!m_node->next || !m_node->prev)
			{
				throw std::logic_error("can not end or rend iterator value");
			}
			return m_node->data.get();
		}
		CIterator() = delete;
		std::shared_ptr<Node<T>> m_node = nullptr;
	};
	typedef CIterator<T> IteratorType;
	typedef std::reverse_iterator<CIterator<T>> CReverseIterator;

	IteratorType begin()
	{
		return IteratorType(m_firstNode->next);
	}
	
	IteratorType end()
	{
		return IteratorType(m_lastNode);
	}

	const IteratorType begin()const
	{
		return IteratorType(m_firstNode->next);
	}

	const IteratorType end()const
	{
		return IteratorType(m_lastNode);
	}

	const IteratorType cbegin()const
	{
		return IteratorType(m_firstNode->next);
	}

	const IteratorType cend()const
	{
		return IteratorType(m_lastNode);
	}

	CReverseIterator rbegin()
	{
		return CReverseIterator(end());
	}

	CReverseIterator rend()
	{
		return CReverseIterator(begin());
	}

	const CReverseIterator rbegin() const
	{
		return CReverseIterator(end());
	}

	const CReverseIterator rend() const
	{
		return CReverseIterator(begin());
	}

	const CReverseIterator crbegin() const
	{
		return CReverseIterator(cend());
	}

	const CReverseIterator crend() const
	{
		return CReverseIterator(cbegin());
	}

	T & GetBackElement()
	{
		if (empty())
		{
			throw std::logic_error("list is empty");
		}
		return *m_lastNode->prev->data;
	}

	T const& GetBackElement()const
	{
		if (empty())
		{
			throw std::logic_error("list is empty");
		}
		return *m_lastNode->prev->data;
	}

	T & GetFrontElement()
	{
		if (empty())
		{
			throw std::logic_error("list is empty");
		}
		return *m_firstNode->next->data;
	}

	T const& GetFrontElement()const
	{
		if (empty())
		{
			throw std::logic_error("list is empty");
		}
		return *m_firstNode->next->data;
	}

	void insert(const IteratorType & it, const T & data)
	{
		auto newNode = std::make_shared<Node<T>>(data, it.m_node->prev, it.m_node);
		it.m_node->prev->next = newNode;
		it.m_node->prev = newNode;
		++m_size;
	}

	void erase(const IteratorType & it)
	{
		if (!it.m_node->prev || !it.m_node->next)
		{
			throw std::logic_error("can not deleted the element of end or rend iterator");
		}
		it.m_node->next->prev = it.m_node->prev;
		it.m_node->prev->next = it.m_node->next;
		--m_size;
	}

private:
	void ClearLinks(std::shared_ptr<Node<T>> const & firstNode)
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
	
	size_t m_size = 0;
	std::shared_ptr<Node<T>> m_firstNode = std::make_shared<Node<T>>();
	std::shared_ptr<Node<T>> m_lastNode = std::make_shared<Node<T>>();
};

template <class T>
bool operator==(const CMyList<T> & lhs, const CMyList<T> & rhs)
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

template <class T>
bool operator!=(const CMyList<T> & lhs, const CMyList<T> & rhs)
{
	return !(lhs == rhs);
}
