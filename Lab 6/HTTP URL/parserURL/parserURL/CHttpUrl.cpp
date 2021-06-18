#include "CHttpUrl.h"
#include <algorithm>
#include <string>
#include <regex>
#include <map>
#include <iostream>

using Regex = regex;

const map<string, Protocol> protocols =
{
    {"http", Protocol::HTTP},
    {"https", Protocol::HTTPS}
};

const map<Protocol, unsigned short> ports =
{
    {Protocol::HTTP, 80},
    {Protocol::HTTPS, 443}
};

const int PROTOCOL_INDEX = 1;
const int DOMAIN_INDEX = 2;
const int PORT_INDEX = 3;
const int DOCUMENT_INDEX = 4;

const size_t NOT_FOUND = string::npos;

const string ALLOWED_DOMAIN_SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=";

//construtctors
CHttpUrl::CHttpUrl(string const& url) 
{
    string lowerUrl;
    lowerUrl.resize(url.length());
    transform(url.begin(), url.end(), lowerUrl.begin(), [](char ch) {return tolower(ch); });
    smatch splitedUrl;
    Regex regex("(.+):\/\/([a-zA-Z0-9.]+)(:[0-9]+)?\/?(.*)?");
    if (regex_match(lowerUrl, splitedUrl, regex)) 
    {
        string protocolStr = splitedUrl[PROTOCOL_INDEX];
        m_domain = splitedUrl[DOMAIN_INDEX];
        string portStr = splitedUrl[PORT_INDEX];
        m_document = splitedUrl[DOCUMENT_INDEX];

        m_protocol = GetProtocolFromRequest(protocolStr);
        if (!isCorrectProtocol())
        {
            throw CUrlParsingError("Invalid protocol");
        }

        m_port = GetPortFromRequest(portStr);
        if(!isCorrectPort())
        {
            throw CUrlParsingError("Invalid port");
        }

        addMissingSlash(m_document);
        return;
    }
    throw CUrlParsingError("Incorrect url format. Must be <protocol> <host> < port?> <document?>");
}

CHttpUrl::CHttpUrl
(
    string const& domain,
    string const& document,
    Protocol protocol
)
    : m_protocol(protocol),
    m_domain(domain),
    m_document(document)
{
    if (!isCorrectDomain()) 
    {
        throw CUrlParsingError("Invalid domain");
    }
    addMissingSlash(m_document);
    m_port = ports.at(m_protocol);
}

CHttpUrl::CHttpUrl
(
    string const& domain,
    string const& document,
    Protocol protocol,
    unsigned short port
) 
    :m_protocol(protocol),
    m_domain(domain),
    m_port(port),
    m_document(document)
{
    if (!isCorrectDomain()) 
    {
        throw CUrlParsingError("Incorrect domain");
    }
    if (!isCorrectPort())
    {
        throw CUrlParsingError("Incorrect port");
    }
    addMissingSlash(m_document);
}

//Getters
string CHttpUrl::GetURL() 
{
    return (ProtocolString() + "://" + m_domain + FilterPort() + m_document);
}
 
string CHttpUrl::GetDomain() const
{
    return m_domain;
}

string CHttpUrl::GetDocument() const
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


//private methods
Protocol CHttpUrl::GetProtocolFromRequest(string protocolStr) const
{
    if (protocolStr == "http")
    {
        return Protocol::HTTP;
    }
    else if (protocolStr == "https")
    {
        return Protocol::HTTPS;
    }
    return Protocol::WITHOUT_PROTOCOL;
}

unsigned short CHttpUrl::GetPortFromRequest(string portStr) const 
{
    if (portStr.empty()) 
    {
        return ports.at(m_protocol);
    }
    portStr.erase(0, 1);
    return stoi(portStr);
}

void CHttpUrl::addMissingSlash(string& document) 
{
    if (document.empty()) 
    {
        return;
    }

    if (document[0] != '/') 
    {
        document = '/' + document;
    }
}

string CHttpUrl::ProtocolString() const 
{
    switch (m_protocol) {
    case Protocol::HTTP:
        return "http";
    case Protocol::HTTPS:
        return "https";
    default:
        return "NO_PROTOCOL";
    }
}

string CHttpUrl::FilterPort() 
{
    for (auto port : ports) 
    {
        if (port.second == m_port)
            return "";
    }
    return (":" + to_string(m_port));
}

bool CHttpUrl::isCorrectProtocol() const
{
    if (m_protocol == Protocol::WITHOUT_PROTOCOL) 
    {
        return false;
    }
    return true;
}
bool CHttpUrl::isCorrectDomain()  const
{
    if (m_domain.empty()) 
    {
        return false;
    }
    if (m_domain.find_first_not_of(ALLOWED_DOMAIN_SYMBOLS) != NOT_FOUND)
    {
        return false;
    }
    return true;
}


bool CHttpUrl::isCorrectPort() const
{
    return (m_port > 0 && m_port < 65535);
}