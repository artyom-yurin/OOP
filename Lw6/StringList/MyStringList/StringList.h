#pragma once

#include <string>
#include <memory>

class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node *prev;
		std::unique_ptr<Node> next;
	};
public:
	size_t GetSize()const;
	void Append(const std::string& data);
	void push_front(const std::string& data);
	bool empty()const;
	void clear();

	class CIterator
	{
		friend CStringList;
		CIterator(Node *node, bool isReverse = false);
	public:
		CIterator() = default;
		std::string & operator*()const;
		CIterator & operator++();
		CIterator & operator--();
		bool operator==(const CIterator & it) const;

	private:
		Node *m_node = nullptr;
		bool m_isReverse = false;
	};

	CIterator rbegin();
	CIterator rend();

	const CIterator crbegin() const;
	const CIterator crend() const;

	CIterator begin();
	CIterator end();

	const CIterator cbegin()const;
	const CIterator cend()const;

	std::string & GetBackElement();
	std::string const& GetBackElement()const;
	std::string & GetFrontElement();
	std::string const& GetFrontElement()const;

	void insert(const CIterator & it, const std::string & data);
	void erase(const CIterator & it);
private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;
};