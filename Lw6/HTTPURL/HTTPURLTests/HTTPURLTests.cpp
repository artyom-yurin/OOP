#include "stdafx.h"
#include "../HTTPURL/HttpUrl.h"
#include "../HTTPURL/UrlParsingError.h"

BOOST_AUTO_TEST_SUITE(HttpUrl)

	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_protocol)
	{
		BOOST_CHECK_THROW(CHttpUrl url("hsspt://local.host/index.html"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_domain)
	{
		BOOST_CHECK_THROW(CHttpUrl url("https:///index.html"), CUrlParsingError);
	}
	
	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_port)
	{
		BOOST_CHECK_THROW(CHttpUrl url("https://localhost:0/index.html"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl url("https://localhost:port/index.html"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_document)
	{
		BOOST_CHECK_THROW(CHttpUrl url("https://localhost//"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_not_be_create_with_user_data_with_incorrect_domain)
	{
		BOOST_CHECK_THROW(CHttpUrl url("", "index.html"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_not_be_create_with_user_data_with_incorrect_document)
	{
		BOOST_CHECK_THROW(CHttpUrl url("localhost", "//"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_not_be_create_with_user_data_with_incorrect_port)
	{
		BOOST_CHECK_THROW(CHttpUrl url("localhost", "/index.html", HTTPS, 0), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(can_be_created_from_string_with_string_domain)
	{
		CHttpUrl url("https://localhost/index.html");
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
		BOOST_CHECK_EQUAL(url.GetDomain(), "localhost");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://localhost/index.html");
	}

	BOOST_AUTO_TEST_CASE(can_be_created_from_string_with_standart_port)
	{
		CHttpUrl url("https://127.0.0.1?");
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/?");
		BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://127.0.0.1/?");
	}
	
	BOOST_AUTO_TEST_CASE(can_be_created_from_string_with_custom_port)
	{
		CHttpUrl url("http://127.0.0.1:344?");
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTP);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/?");
		BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
		BOOST_CHECK_EQUAL(url.GetPort(), 344);
		BOOST_CHECK_EQUAL(url.GetURL(), "http://127.0.0.1:344/?");
	}

	BOOST_AUTO_TEST_CASE(can_be_create_with_user_data_with_standart_port)
	{
		{
			CHttpUrl url("127.0.0.1", "index.html", HTTPS, 443);
			BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
			BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
			BOOST_CHECK_EQUAL(url.GetPort(), 443);
			BOOST_CHECK_EQUAL(url.GetURL(), "https://127.0.0.1/index.html");
		}
		
		{
			CHttpUrl url("127.0.0.1", "index.html");
			BOOST_CHECK_EQUAL(url.GetProtocol(), HTTP);
			BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
			BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
			BOOST_CHECK_EQUAL(url.GetPort(), 80);
			BOOST_CHECK_EQUAL(url.GetURL(), "http://127.0.0.1/index.html");
		}
	}

	BOOST_AUTO_TEST_CASE(can_be_create_with_user_data_with_custom_port)
	{
		CHttpUrl url("127.0.0.1", "index.html", HTTP, 7000);
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTP);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
		BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
		BOOST_CHECK_EQUAL(url.GetPort(), 7000);
		BOOST_CHECK_EQUAL(url.GetURL(), "http://127.0.0.1:7000/index.html");
	}

	BOOST_AUTO_TEST_CASE(can_give_info_about_myself)
	{
		CHttpUrl url("127.0.0.1", "index.html", HTTP, 7000);
		std::string correctResult = "URL: http://127.0.0.1:7000/index.html\n";
		correctResult += "Protocol: http\n";
		correctResult += "Domain: 127.0.0.1\n";
		correctResult += "Port: 7000\n";
		correctResult += "Document: /index.html\n";
		BOOST_CHECK_EQUAL(url.ToString(), correctResult);
	}

BOOST_AUTO_TEST_SUITE_END()
