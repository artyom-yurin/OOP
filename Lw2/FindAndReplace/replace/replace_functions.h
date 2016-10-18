#pragma once

std::string FindAndReplace(const std::string & subject, const std::string & search, const std::string & replace);

inline std::string GetString(std::istream & input)
{
	std::string line;

	if (!getline(input, line))
	{
		line = "";
	}

	return line;
}

inline bool PrintString(std::ostream & output, std::string subject)
{
	if (!(output << subject << "\n"))
	{
		return false;
	}

	return true;
}