#include "stdafx.h"
#include "../MyStringList/StringList.h"

using namespace std;

struct EmptyStringList
{
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)

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

		BOOST_AUTO_TEST_CASE(can_insert_element_in_place_of_the_iterator)
		{
			list.Append("second");
			auto it = list.begin();
			list.insert(it, "first");
			++it;
			list.insert(it, "fourth");
			it = list.begin();
			++it;
			++it;
			list.insert(it, "third");
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
			list.Append("third");
			list.Append("fourth");
			auto it = list.begin();
			++it;
			list.erase(it);
			it = list.begin();
			list.erase(it);
			it = list.end();
			list.erase(it);
			it = list.begin();
			BOOST_CHECK_EQUAL(*it, "third");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(iterator)

		BOOST_AUTO_TEST_CASE(when_list_is_empty_begin_and_end_iterator_are_equal)
		{
			CStringList emptyList;
			BOOST_CHECK(emptyList.begin() == emptyList.end());
			BOOST_CHECK(emptyList.cbegin() == emptyList.cend());
		}

		BOOST_AUTO_TEST_CASE(can_be_increnenting_and_decrementing)
		{
			list.Append("first");
			list.Append("second");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
			--iter;
			BOOST_CHECK_EQUAL(*iter, "first");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
