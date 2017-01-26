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

	class CIterator
	{
		friend CStringList;
		CIterator(std::shared_ptr<Node> const & node);
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::string value_type;
		typedef ptrdiff_t difference_type;
		typedef std::string* pointer;
		typedef std::string& reference;
		std::string & operator*()const;
		CIterator & operator++();
		CIterator operator++(int);
		CIterator & operator--();
		CIterator operator--(int);
		bool operator==(const CIterator & it) const;
		bool operator!=(const CIterator & it) const;

	private:
		Node * CIterator::operator->() const
		{
			if (!m_node->next || !m_node->prev)
			{
				throw std::logic_error("can not end or rend iterator value");
			}
			return m_node.get();
		}
		CIterator() = delete;
		std::shared_ptr<Node> m_node = nullptr;
	};
	typedef std::reverse_iterator<CIterator> CReverseIterator;
	CIterator begin();
	CIterator end();

	const CIterator begin()const;
	const CIterator end()const;

	const CIterator cbegin()const;
	const CIterator cend()const;

	CReverseIterator rbegin();
	CReverseIterator rend();

	const CReverseIterator rbegin() const;
	const CReverseIterator rend() const;

	const CReverseIterator crbegin() const;
	const CReverseIterator crend() const;

	std::string & GetBackElement();
	std::string const& GetBackElement()const;
	std::string & GetFrontElement();
	std::string const& GetFrontElement()const;

	void insert(const CIterator & it, const std::string & data);
	void erase(const CIterator & it);
private:
	size_t m_size = 0;
	std::shared_ptr<Node> m_firstNode = std::make_shared<Node>("", nullptr, nullptr);
	std::shared_ptr<Node> m_lastNode = std::make_shared<Node>("", nullptr, nullptr);
};

bool operator==(const CStringList & lhs, const CStringList & rhs);
bool operator!=(const CStringList & lhs, const CStringList & rhs);
