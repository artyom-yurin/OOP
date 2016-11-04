#include "stdafx.h"
#include "replace_functions.h"

std::string FindAndReplace(const std::string & subject, const std::string & search, const std::string & replace)
{
	if (!search.empty())
	{
		std::string newString;
		size_t startPosition = 0;
		auto positionString = subject.find(search, 0);

		while (positionString != std::string::npos)
		{
			newString.append(subject, startPosition, positionString - startPosition);
			newString.append(replace);
			startPosition = positionString + search.size();
			positionString = subject.find(search, startPosition);
		}

		newString.append(subject, startPosition);

		return newString;
	}
	else
	{
		return subject;
	}
}

