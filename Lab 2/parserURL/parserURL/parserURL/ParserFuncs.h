#pragma once
#include <string>
using namespace std;

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP,
    WITHOUT_PROTOCOL
};

Protocol GetProtocol(string str_protocol);
int GetPortFromProtocol(Protocol protocol);
bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document);
void PrintParsedURL(Protocol protocol, int port, string host, string document);