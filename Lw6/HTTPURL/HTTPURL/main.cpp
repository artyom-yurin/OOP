#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

int main()
{
	std::string urlStr;
	while (std::getline(std::cin, urlStr))
	{
		try
		{
			CHttpUrl url(urlStr);
			std::cout << "\n" << url.ToString() << "\n";
		}
		catch (CUrlParsingError & err)
		{
			std::cout << "\n" << err.what() << "\n" << std::endl;
		}
	}
	return 0;
}

