#include "stdafx.h"
#include "StringList.h"
#include <iostream>

int main()
{
	CStringList list;
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
	std::cout << *it << "\n";
	++it;
	std::cout << *it << "\n";
	++it;
	std::cout << *it << "\n";
	++it;
	std::cout << *it << "\n";

    return 0;
}

