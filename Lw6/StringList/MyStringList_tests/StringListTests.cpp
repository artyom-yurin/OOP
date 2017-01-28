#include "stdafx.h"
#include "../MyStringList/StringList.h"

using namespace std;

struct EmptyStringList
{
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)
	
	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		BOOST_CHECK(list == list);
		CStringList otherList;
		BOOST_CHECK(list == otherList);
		otherList.Append("hello");
		BOOST_CHECK(list != otherList);
		list.Append("hello");
		BOOST_CHECK(list == otherList);
		list.Append("hola");
		otherList.Append("aloh");
		BOOST_CHECK(list != otherList);
	}

	BOOST_AUTO_TEST_CASE(can_not_get_element_from_empty_list)
	{
		BOOST_CHECK_THROW(list.GetFrontElement(), std::logic_error);
		BOOST_CHECK_THROW(list.GetBackElement(), std::logic_error);
		const CStringList constList;
		BOOST_CHECK_THROW(constList.GetFrontElement(), std::logic_error);
		BOOST_CHECK_THROW(constList.GetBackElement(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(can_get_const_last_element)
	{
		list.Append("halo");
		list.Append("hello");
		const auto constList(list);
		BOOST_CHECK_EQUAL(constList.GetBackElement(), "hello");
	}

	BOOST_AUTO_TEST_CASE(can_get_const_first_element)
	{
		list.Append("halo");
		list.Append("hello");
		const auto constList(list);
		BOOST_CHECK_EQUAL(constList.GetFrontElement(), "halo");
	}

	BOOST_AUTO_TEST_CASE(can_be_copied)
	{
		CStringList tempList;
		tempList.Append("hello");
		tempList.Append("hi");
		tempList.Append("hola");
		list = tempList;
		BOOST_CHECK_EQUAL(tempList.GetSize(), 3);
		BOOST_CHECK_EQUAL(list.GetSize(), 3);
		auto it = list.begin();
		BOOST_CHECK_EQUAL(*it, "hello");
	}
	
	BOOST_AUTO_TEST_CASE(can_be_moved)
	{
		CStringList tempList;
		tempList.Append("hello");
		tempList.Append("hi");
		tempList.Append("hola");
		list = std::move(tempList);
		BOOST_CHECK_EQUAL(tempList.GetSize(), 0);
		BOOST_CHECK_EQUAL(list.GetSize(), 3);
		auto it = list.begin();
		BOOST_CHECK_EQUAL(*it, "hello");
	}

	BOOST_AUTO_TEST_CASE(can_not_move_themselves)
	{
		CStringList tempList;
		tempList.Append("hello");
		tempList.Append("hi");
		tempList.Append("hola");
		tempList = std::move(tempList);
		BOOST_CHECK_EQUAL(tempList.GetSize(), 3);
		auto it = tempList.begin();
		BOOST_CHECK_EQUAL(*it, "hello");
	}

	BOOST_AUTO_TEST_SUITE(when_created)

		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
			BOOST_CHECK(list.empty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appeding_a_string)

		BOOST_AUTO_TEST_CASE(can_be_clear)
		{
			list.Append("hello");
			list.Append("hello");
			list.Append("hello");
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), 4);
			list.clear();
			BOOST_CHECK_EQUAL(list.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			BOOST_CHECK(list.empty());
			auto oldSize = list.GetSize();
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
			list.push_front("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 3);
			list.push_front("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 4);
			BOOST_CHECK(!list.empty());
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.Append("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.push_front("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.push_front("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "goodbye");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.Append("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_const_iterator_to_first_element)
		{
			list.Append("hello");
			auto it = list.cbegin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_last_element)
		{
			list.Append("hello");
			list.Append("hi");
			auto it = list.end();
			--it;
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_const_iterator_to_last_element)
		{
			list.Append("hello");
			list.Append("hi");
			auto it = list.cend();
			--it;
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_reverse_iterator_to_last_element)
		{
			list.Append("hello");
			list.Append("hi");
			auto it = list.rbegin();
			BOOST_CHECK_EQUAL(*it, "hi");
			BOOST_CHECK_EQUAL(*(++it), "hello");
			BOOST_CHECK_THROW(*(++it), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_reverse_iterator_to_last_element_const)
		{
			list.Append("hello");
			list.Append("hi");
			const CStringList constList(list);
			auto it = constList.rbegin();
			BOOST_CHECK_EQUAL(*it, "hi");
			BOOST_CHECK_EQUAL(*(++it), "hello");
			BOOST_CHECK_THROW(*(++it), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_const_reverse_iterator_to_last_element)
		{
			list.Append("hello");
			list.Append("hi");
			auto it = list.crbegin();
			BOOST_CHECK_EQUAL(*it, "hi");
			BOOST_CHECK_EQUAL(*(++it), "hello");
			BOOST_CHECK_THROW(*(++it), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(can_insert_element_in_place_of_the_iterator)
		{
			BOOST_CHECK(list.empty());
			list.Append("second");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			list.insert(it, "first");
			++it;
			BOOST_CHECK_EQUAL(list.GetSize(), 2);
			list.insert(it, "fourth");
			BOOST_CHECK_EQUAL(list.GetSize(), 3);
			it = list.begin();
			++it;
			++it;
			list.insert(it, "third");
			BOOST_CHECK_EQUAL(list.GetSize(), 4);
			it = list.begin();
			BOOST_CHECK_EQUAL(*it, "first");
			++it;
			BOOST_CHECK_EQUAL(*it, "second");
			++it;
			BOOST_CHECK_EQUAL(*it, "third");
			++it;
			BOOST_CHECK_EQUAL(*it, "fourth");
		}

		BOOST_AUTO_TEST_CASE(can_delete_the_item_in_place_iterator)
		{
			list.Append("first");
			list.Append("second");
			auto it = list.begin();
			list.erase(it);
			it = list.begin();
			BOOST_CHECK_EQUAL(*it, "second");
			it = list.end();
			BOOST_CHECK_THROW(list.erase(it), std::logic_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(iterator)

		BOOST_AUTO_TEST_CASE(can_be_compared)
		{
			 BOOST_CHECK(list.begin() == list.cbegin());
			 list.Append("hello");
			 BOOST_CHECK(list.begin() != list.end());
		}
		
		BOOST_AUTO_TEST_CASE(can_give_pointer)
		{
			list.Append("Hello");
			BOOST_CHECK_EQUAL(list.begin()->length(), 5);
		}

		BOOST_AUTO_TEST_CASE(can_not_take_the_value_of_end_or_rend_iterator)
		{
			BOOST_CHECK_THROW(*list.end(), std::logic_error);
			BOOST_CHECK_THROW(*list.cend(), std::logic_error);
			BOOST_CHECK_THROW(*list.rend(), std::logic_error);
			BOOST_CHECK_THROW(*list.crend(), std::logic_error);
			const CStringList constList;
			BOOST_CHECK_THROW(*constList.end(), std::logic_error);
			BOOST_CHECK_THROW(*constList.rend(), std::logic_error);
		}
		
		BOOST_AUTO_TEST_CASE(can_not_take_pointer_of_end_or_rend_iterator)
		{
			BOOST_CHECK_THROW(list.end()->length(), std::logic_error);
			BOOST_CHECK_THROW(list.cend()->length(), std::logic_error);
			BOOST_CHECK_THROW(list.rend()->length(), std::logic_error);
			BOOST_CHECK_THROW(list.crend()->length(), std::logic_error);
			const CStringList constList;
			BOOST_CHECK_THROW(constList.end()->length(), std::logic_error);
			BOOST_CHECK_THROW(constList.rend()->length(), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(can_be_increnenting_and_decrementing)
		{
			list.Append("first");
			list.Append("second");
			auto iter = list.begin();
			--iter;
			BOOST_CHECK_THROW(--iter, std::logic_error);
			iter = list.begin();
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
			--iter;
			BOOST_CHECK_EQUAL(*iter, "first");
			BOOST_CHECK_EQUAL(*(iter++), "first");
			BOOST_CHECK_EQUAL(*(iter--), "second");
			iter = list.end();
			BOOST_CHECK_THROW(++iter, std::logic_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
