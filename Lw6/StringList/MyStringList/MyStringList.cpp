#include "stdafx.h"
#include "StringList.h"

int main()
{
	CStringList list;
	CStringList otherList;
	if ((list == otherList))
	{
		int i = 10;
		++i;
	}
	otherList.Append("hello");
    return 0;
}

