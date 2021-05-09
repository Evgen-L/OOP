#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../parserURL/ParserFuncs.h"

SCENARIO("ParseURL: empty url")
{
	cout << "ParseURL: empty url" << endl;
	string url = "";
	string host, document;
	Protocol protocol;
	int port;
	bool result;
	result = ParseURL(url, protocol, port, host, document);
	REQUIRE(result == false);
	cout << "Done" << endl << endl;
}

SCENARIO("ParseURL: incorrect protocol")
{
	cout << "ParseURL: incorrect protocol" << endl;
	string url = "httpss://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	string host, document;
	Protocol protocol;
	int port;
	bool result;
	result = ParseURL(url, protocol, port, host, document);
	REQUIRE(result == false);
	cout << "Done" << endl << endl;
}

SCENARIO("ParseURL: get port from protocol without port it in url #1")
{
	cout << "ParseURL: get port from protocol without port it in url #1" << endl;
	string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((host == "www.mysite.com" && port == 80 && document == "docs/document1.html?page=30&lang=en#title"
		&& protocol == Protocol::HTTP
		));
	cout << "Done" << endl << endl;
}

SCENARIO("ParseURL: get port from protocol without port it in url #2")
{
	cout << "ParseURL: get port from protocol without port it in url #2" << endl;
	string url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((host == "www.mysite.com"
		&& port == 21
		&& document == "docs/document1.html?page=30&lang=en#title"
		&& protocol == Protocol::FTP));
	cout << "Done" << endl << endl;
}

SCENARIO("ParseURL: get port from protocol without port it in url #3")
{
	cout << "ParseURL: get port from protocol without port it in url #3" << endl;
	string url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((host == "www.mysite.com"
		&& port == 443
		&& document == "docs/document1.html?page=30&lang=en#title"
		&& protocol == Protocol::HTTPS));
	cout << "Done" << endl << endl;
}

SCENARIO("ParseURL: with port")
{
	cout << "ParseURL: with port" << endl;
	std::string url = "http://www.mysite.com:59/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((host == "www.mysite.com"
		&& port == 59
		&& document == "docs/document1.html?page=30&lang=en#title"
		&& protocol == Protocol::HTTP));
	cout << "Done" << endl << endl;
}

SCENARIO("ParseURL: port is more limitation")
{
	cout << "ParseURL: port is more limitation" << endl;
	string url = "http://www.mysite.com:65546/docs/document1.html?page=30&lang=en#title";
	string host, document;
	Protocol protocol;
	int port;
	bool result;
	result = ParseURL(url, protocol, port, host, document);
	REQUIRE(result == false);
	cout << "Done" << endl << endl;
}

SCENARIO("ParseURL: without document")
{
	cout << "ParseURL: without document" << endl;
	string url = "http://www.mysite.com";
	string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((host == "www.mysite.com"
		&& port == 80
		&& document == ""
		&& protocol == Protocol::HTTP));
	cout << "Done" << endl << endl;
}
