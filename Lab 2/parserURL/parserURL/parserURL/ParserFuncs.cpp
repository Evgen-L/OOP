#include <iostream>
#include <string>
#include <regex>

using namespace std;
using Regex = regex;

const string HOST = "HOST: ";
const string PORT = "PORT: ";
const string DOC = "DOCUMENT: ";

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP,
    WITHOUT_PROTOCOL
};

Protocol GetProtocol(string protocolStr)
{
    if (protocolStr == "http")
    {
        return Protocol::HTTP;
    }
    else if (protocolStr == "https")
    {
        return Protocol::HTTPS;
    }
    else if (protocolStr == "ftp")
    {
        return Protocol::FTP;
    }
    else 
    {
        return Protocol::WITHOUT_PROTOCOL;
    }
}

int GetPortFromProtocol(Protocol protocol)
{
    switch (protocol)
    {
    case Protocol::HTTP:
        return 80;
        break;
    case Protocol::HTTPS:
        return 443;
        break;
    case Protocol::FTP:
        return 21;
        break;
    default:
        return 0;
        break;
    }
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
    string lowerUrl;
    lowerUrl.resize(url.length());
    transform(url.begin(), url.end(), lowerUrl.begin(), [](char ch) {return tolower(ch); });
    cmatch splitedUrl;
    Regex regex("(http|https|ftp):\/\/([a-zA-Z0-9.]+)(:[0-9]+)?(\/.+)?");
    if (regex_match(lowerUrl.c_str(), splitedUrl, regex))
    {
        protocol = GetProtocol(splitedUrl[1]);
        host = splitedUrl[2];
        if (splitedUrl[3] == "")
        {
            port = GetPortFromProtocol(protocol);
        }
        else 
        {
            string portStr = splitedUrl[3];
            portStr.erase(0, 1);
            if (!(stoi(portStr) < 1 || stoi(portStr) > 65535))
            {
                port = stoi(portStr);
            } 
            else 
            {
                return false;
            }
        }
        if (!(splitedUrl[4] == ""))
        {
            string documentStr = splitedUrl[4].str();
            document = documentStr.substr(1, documentStr.length());
        }
        else
        {
            document = splitedUrl[4];
        }
        return true;
    }
    return false;
}

void PrintParsedURL(Protocol protocol, int port, string host, string document)
{
    cout << HOST;
    cout << host << endl;
    cout << PORT;
    cout << port << endl;
    if (document != "") 
    {
        cout << DOC;
        cout << document;
    }
}