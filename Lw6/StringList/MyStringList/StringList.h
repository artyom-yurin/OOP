#pragma once

#include <string>
#include <memory>

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
	~CStringList();
	size_t GetSize()const;
	void Append(const std::string& data);
	void push_front(const std::string& data);
	bool empty()const;
	void clear();

	class CIterator
	{
		friend CStringList;
		CIterator(std::shared_ptr<Node> const & node);
	public:
		CIterator() = default;
		std::string & operator*()const;
		CIterator & operator++();
		CIterator operator++(int);
		CIterator & operator--();
		CIterator operator--(int);
		bool operator==(const CIterator & it) const;
		bool operator!=(const CIterator & it) const;

	private:
		std::shared_ptr<Node> m_node = nullptr;
	};

	CIterator begin();
	CIterator end();

	const CIterator cbegin()const;
	const CIterator cend()const;

	/*std::reverse_iterator<CIterator> rbegin();
	std::reverse_iterator<CIterator> rend();

	std::reverse_iterator<const CIterator> crbegin() const;
	std::reverse_iterator<const CIterator> crend() const;*/

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