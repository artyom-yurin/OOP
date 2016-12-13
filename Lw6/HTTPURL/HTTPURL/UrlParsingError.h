#pragma once
class CUrlParsingError
	: public std::invalid_argument
{
public:
	explicit CUrlParsingError(std::string const & url) : std::invalid_argument(url) {};
};

