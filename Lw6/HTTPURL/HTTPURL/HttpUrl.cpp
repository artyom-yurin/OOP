#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

const std::string PROTOCOL_PATTERN = "((https)|(http))";
const std::string DOMAIN_PATTERN = "(((\\w|-)+\\.)+\\w+)";
const std::string DOCUMEN_PATTERN = "(((/(\\w|-|\\.|_)+)+/?)|/)";
const std::string QUERY_STRING = "(\\?.*)?";

std::string ProtocolToString(Protocol const & protocol)
{
	if (protocol == HTTP)
	{
		return "http";
	}
	return "https";
}

Protocol StringToProtocol(std::string const & protocol)
{
	if (protocol == "http")
	{
		return HTTP;
	}
	else if (protocol == "https")
	{
		return HTTPS;
	}
	throw CUrlParsingError("Incorrect protocol");
}

Protocol GetProtocolFromUrl(std::string & url)
{
	if(std::regex_match(url, std::regex(PROTOCOL_PATTERN + ".*")))
	{
		std::string protocol = url.substr(0, url.find("://"));
		url.erase(0, protocol.length() + 3);
		return StringToProtocol(protocol);
	}
	throw CUrlParsingError("Incorrect protocol");
}

std::string GetDomainFromUrl(std::string & url)
{
	if (std::regex_match(url, std::regex(DOMAIN_PATTERN + ".*")))
	{
		auto domainEndPos = url.find(":");
		if (domainEndPos == std::string::npos)
		{
			domainEndPos = url.find("/");
			if (domainEndPos == std::string::npos)
			{
				domainEndPos = url.length();
			}
		}
		std::string domain = url.substr(0, domainEndPos);
		url.erase(0, domainEndPos);
		return domain;
	}
	throw CUrlParsingError("Incorrect domain");
}

std::string GetPortFromUrl(std::string & url)
{
	if (std::regex_match(url, std::regex("(:\\d+)?($|\\?.*|/.*)")))
	{
		if ((url.length() >= 1) && (url[0] == ':'))
		{
			url.erase(0, 1);
		}
		auto portEndPos = url.find("/");
		if (portEndPos == std::string::npos)
		{
			portEndPos = url.length();
		}
		std::string port = url.substr(0, portEndPos);
		url.erase(0, port.length());
		return port;
	}
	throw CUrlParsingError("Incorrect Port");
}

CHttpUrl::CHttpUrl(std::string const & url)
{
	std::string copyUrl = url;
	m_protocol = GetProtocolFromUrl(copyUrl);
	m_domain = GetDomainFromUrl(copyUrl);
	std::string port = GetPortFromUrl(copyUrl);
	if (port == "")
	{
		if (m_protocol == HTTP)
		{
			m_port = 80;
		}
		else
		{
			m_port = 443;
		}
	}
	else //TODO: Check Port
	{
		m_port = stoi(port);
	}
	if (copyUrl.length() == 0 || copyUrl[0] == '?')
	{
		copyUrl = "/" + copyUrl;
	}
	if (std::regex_match(copyUrl, std::regex(DOCUMEN_PATTERN + QUERY_STRING)))
	{
		m_document = copyUrl;
	}
	else
	{
		throw CUrlParsingError("Incorrect document");
	}
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
{
	if (!std::regex_match(domain, std::regex(DOMAIN_PATTERN)))
	{
		throw CUrlParsingError("Incorrect domain");
	}
	std::string newDocument = document;
	if (document.length() == 0 || document[0] != '/')
	{
		newDocument = "/" + document;	
	}
	if (!std::regex_match(newDocument, std::regex(DOCUMEN_PATTERN + QUERY_STRING)))
	{
		throw CUrlParsingError("Incorrect document");
	}
	m_domain = domain;
	m_document = newDocument;
	m_port = port;
	m_protocol = protocol;
}

std::string CHttpUrl::GetURL() const
{
	std::stringstream url;
	url << ProtocolToString(m_protocol)
		<< "://" << m_domain;
	if (!((m_protocol == HTTP && m_port == 80) || (m_protocol == HTTPS && m_port == 443)))
	{
		url << ":" << m_port;
	}
	url << m_document;
	return url.str();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
