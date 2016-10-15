#pragma once

#include "stdafx.h"

std::string FindAndReplace(const std::string & subject, const std::string & search, const std::string & replace)
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

std::string GetString(std::istream & input)
{
	std::string line;

	if (!getline(input, line))
	{
		line = "";
	}

	return line;
}

bool PrintString(std::ostream & output, std::string subject)
{
	if (!(output << subject << "\n"))
	{
		return false;
	}

	return true;
}