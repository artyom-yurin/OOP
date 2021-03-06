#pragma once

#include <string>
#include <memory>
#include <iterator>
#include <boost/optional.hpp>

template <typename T>
struct Node
{
	Node(boost::optional<T> const & data, std::shared_ptr<Node<T>> const & prev, std::shared_ptr<Node<T>> const & next)
		: data(data), prev(prev), next(next)
	{}
	boost::optional<T> data;
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

	template <class DataT>
	class CIterator
	{
		friend CMyList;
		CIterator(std::shared_ptr<Node<T>> const & node)
			:m_node(node)
		{
		}
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef DataT value_type;
		typedef ptrdiff_t difference_type;
		typedef DataT* pointer;
		typedef DataT& reference;
		operator CIterator<const DataT>()
		{
			return CIterator<const DataT>(m_node);
		}
		DataT & operator*()const
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

		friend bool operator==(const CIterator & lhs, const CIterator & rhs)
		{
			return (lhs.m_node == rhs.m_node);
		}

		friend bool operator!=(const CIterator & lhs, const CIterator & rhs)
		{
			return (lhs.m_node != rhs.m_node);
		}

		DataT * operator->() const
		{
			if (!m_node->next || !m_node->prev)
			{
				throw std::logic_error("can not take pointer of end or rend iterator");
			}
			return m_node->data.get_ptr();
		}

	private:
		CIterator() = delete;
		std::shared_ptr<Node<T>> m_node = nullptr;
	};
	typedef CIterator<T> IteratorType;
	typedef CIterator<const T> ConstIteratorType;
	typedef std::reverse_iterator<CIterator<T>> ReverseIteratorType;
	typedef std::reverse_iterator<CIterator<const T>> ConstReverseIteratorType;

	IteratorType begin()
	{
		return IteratorType(m_firstNode->next);
	}
	
	IteratorType end()
	{
		return IteratorType(m_lastNode);
	}

	ConstIteratorType begin()const
	{
		return ConstIteratorType(m_firstNode->next);
	}

	ConstIteratorType end()const
	{
		return ConstIteratorType(m_lastNode);
	}

	ConstIteratorType cbegin()const
	{
		return ConstIteratorType(m_firstNode->next);
	}

	ConstIteratorType cend()const
	{
		return ConstIteratorType(m_lastNode);
	}

	ReverseIteratorType rbegin()
	{
		return ReverseIteratorType(end());
	}

	ReverseIteratorType rend()
	{
		return ReverseIteratorType(begin());
	}

	ConstReverseIteratorType rbegin() const
	{
		return ConstReverseIteratorType(end());
	}

	ConstReverseIteratorType rend() const
	{
		return ConstReverseIteratorType(begin());
	}

	ConstReverseIteratorType crbegin() const
	{
		return ConstReverseIteratorType(cend());
	}

	ConstReverseIteratorType crend() const
	{
		return ConstReverseIteratorType(cbegin());
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

	void insert(const ConstIteratorType & it, const T & data)
	{
		auto newNode = std::make_shared<Node<T>>(data, it.m_node->prev, it.m_node);
		it.m_node->prev->next = newNode;
		it.m_node->prev = newNode;
		++m_size;
	}

	void erase(const ConstIteratorType & it)
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
	std::shared_ptr<Node<T>> m_firstNode = std::make_shared<Node<T>>(boost::none, nullptr, nullptr);
	std::shared_ptr<Node<T>> m_lastNode = std::make_shared<Node<T>>(boost::none, nullptr, nullptr);
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
