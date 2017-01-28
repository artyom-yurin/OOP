#pragma once

#include <string>
#include <memory>
#include <iterator>

struct Node
{
	Node(std::string const & data, std::shared_ptr<Node> const & prev, std::shared_ptr<Node> const & next)
		: data(data), prev(prev), next(next)
	{
	}
	std::string data;
	std::shared_ptr<Node> prev;
	std::shared_ptr<Node> next;
};

class CStringList
{
public:
	CStringList();
	CStringList(const CStringList & list);
	CStringList(CStringList && list);
	~CStringList();
	size_t GetSize()const;
	void Append(const std::string& data);
	void push_front(const std::string& data);
	bool empty()const;
	void clear();

	CStringList & operator=(const CStringList & list);
	CStringList & operator=(CStringList && list);

	template <class T>
	class CIterator
	{
		friend CStringList;
		CIterator(std::shared_ptr<Node> const & node)
			:m_node(node)
		{
		}
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
		operator CIterator<const T>()
		{
			return CIterator<const T>(m_node);
		}
		T & operator*()const
		{
			if (!m_node->prev || !m_node->next)
			{
				throw std::logic_error("can not take the value of end or rend iterator");
			}
			return m_node->data;
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

		T * operator->() const
		{
			if (!m_node->next || !m_node->prev)
			{
				throw std::logic_error("can not take pointer of end or rend iterator");
			}
			return &m_node->data;
		}

	private:
		CIterator() = delete;
		std::shared_ptr<Node> m_node = nullptr;
	};
	typedef CIterator<std::string> IteratorType;
	typedef CIterator<const std::string> ConstIteratorType;
	typedef std::reverse_iterator<CIterator<std::string>> ReverseIteratorType;
	typedef std::reverse_iterator<CIterator<const std::string>> ConstReverseIteratorType;
	IteratorType begin();
	IteratorType end();

	ConstIteratorType begin()const;
	ConstIteratorType end()const;

	ConstIteratorType cbegin()const;
	ConstIteratorType cend()const;

	ReverseIteratorType rbegin();
	ReverseIteratorType rend();

	ConstReverseIteratorType rbegin() const;
	ConstReverseIteratorType rend() const;

	ConstReverseIteratorType crbegin() const;
	ConstReverseIteratorType crend() const;

	std::string & GetBackElement();
	std::string const& GetBackElement()const;
	std::string & GetFrontElement();
	std::string const& GetFrontElement()const;

	
	void insert(const ConstIteratorType & it, const std::string & data);
	void erase(const ConstIteratorType & it);
private:
	size_t m_size = 0;
	std::shared_ptr<Node> m_firstNode = std::make_shared<Node>("", nullptr, nullptr);
	std::shared_ptr<Node> m_lastNode = std::make_shared<Node>("", nullptr, nullptr);
};

bool operator==(const CStringList & lhs, const CStringList & rhs);
bool operator!=(const CStringList & lhs, const CStringList & rhs);
