// urlPraserTESTS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../parserURL/CHttpUrl.h"
#include "../parserURL/CUrlParsingError.h"

SCENARIO("constructors") 
{
	cout << "constructors\n\n";
	cout << "with url argument\n\n";
	{
		cout << "simple url\n";
		cout << "http://www.mysite.com/docs/document1.html?page=30&lang=en#title" << endl;
		CHttpUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetURL() == "http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetPort() == 80);
		cout << "Done\n\n";
	}

	{
		cout << "indicating the port 8080\n";
		cout << "http://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title" << endl;
		CHttpUrl url("http://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetURL() == "http://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetPort() == 8080);
		cout << "Done\n\n";
	}

	{
		cout << "protocol is https\n";
		cout << "https://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title" << endl;
		CHttpUrl url("https://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetURL() == "https://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetPort() == 8080);
		cout << "Done\n\n";
	}

	{
		cout << "without document\n";
		cout << "https://www.mysite.com:8080" << endl;
		CHttpUrl url("https://www.mysite.com:8080");
		REQUIRE(url.GetURL() == "https://www.mysite.com:8080");
		REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetPort() == 8080);
		cout << "Done\n\n";
	}

	{
		cout << "incorrect url\n";
		cout << "rrrrrr" << endl;
		REQUIRE_THROWS(CHttpUrl ("rrrrrr"));
		cout << "Done\n\n";
	}

	{
		cout << "lack of domain is error\n";
		cout << "https://:8090" << endl;
		REQUIRE_THROWS(CHttpUrl("https://:8090"));
		cout << "Done\n\n";
	}

	{
		cout << "incorrect protocol\n";
		cout << "fps://www.mysite.com:8080" << endl;
		REQUIRE_THROWS(CHttpUrl("fps://www.mysite.com:8080"));
		cout << "Done\n\n\n\n";
	}

	{
		cout << "domain with forbidden symbol \"№\" call error \n";
		cout << "https://www.mysite№1.com:8080" << endl;
		REQUIRE_THROWS(CHttpUrl("www.mysite№1.com"));
		cout << "Done\n\n";
	}



	cout << "with domain, document, protocol\n\n";
	{
		cout << "port to be 80\n";
		cout << "www.mysite.com, \"\", HTTP" << endl;
		CHttpUrl url("www.mysite.com", "", Protocol::HTTP);
		REQUIRE(url.GetURL() == "http://www.mysite.com");
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetPort() == 80);
		REQUIRE(url.GetDocument() == "");
		cout << "Done\n\n";
	}

	{
		cout << "with document\n";
		cout << "www.mysite.com, \"/document.doc\", HTTP" << endl;
		CHttpUrl url("www.mysite.com", "/document.doc", Protocol::HTTP);
		REQUIRE(url.GetURL() == "http://www.mysite.com/document.doc");
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetPort() == 80);
		REQUIRE(url.GetDocument() == "/document.doc");
		cout << "Done\n\n";
	}

	{
		cout << "with document but without slash\n";
		cout << "www.mysite.com, \"document.doc\", HTTP" << endl;
		CHttpUrl url("www.mysite.com", "document.doc", Protocol::HTTP);
		REQUIRE(url.GetURL() == "http://www.mysite.com/document.doc");
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetPort() == 80);
		REQUIRE(url.GetDocument() == "/document.doc");
		cout << "Done\n\n";
	}

	{
		cout << "with empty domain to be error\n";
		cout << "\"\", \"\", HTTP" << endl;
		REQUIRE_THROWS(CHttpUrl ("", "", Protocol::HTTP));
		cout << "Done\n\n\n\n";
	}

	{
		cout << "domain with forbidden symbol \"№\" call error \n";
		cout << "www.mysite№.com, \"\", HTTP" << endl;
		REQUIRE_THROWS(CHttpUrl ("www.mysite№.com", "", Protocol::HTTP));
		cout << "Done\n\n";
	}





	cout << "with domain, document, protocol, port\n\n";
	{
		cout << "with port = 80 url.GetURL() wiil be without port\n";
		cout << "www.mysite.com, \"/document.doc\", HTTP, 80" << endl;
		CHttpUrl url("www.mysite.com", "/document.doc", Protocol::HTTP, 80);
		REQUIRE(url.GetURL() == "http://www.mysite.com/document.doc");
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetPort() == 80);
		REQUIRE(url.GetDocument() == "/document.doc");
		cout << "Done\n\n";
	}

	{
		cout << "with port = 81 url.GetURL() wiil be with port\n";
		cout << "www.mysite.com, \"/document.doc\", HTTP, 81" << endl;
		CHttpUrl url("www.mysite.com", "/document.doc", Protocol::HTTP, 81);
		REQUIRE(url.GetURL() == "http://www.mysite.com:81/document.doc");
		REQUIRE(url.GetDomain() == "www.mysite.com");
		REQUIRE(url.GetPort() == 81);
		REQUIRE(url.GetDocument() == "/document.doc");
		cout << "Done\n\n";
	}

	{
		cout << "with port <= 0 will be error\n";
		cout << "www.mysite.com, \"/document.doc\", HTTP, 0" << endl;
		REQUIRE_THROWS(CHttpUrl("www.mysite.com", "/document.doc", Protocol::HTTP, 0));
		cout << "Done\n\n";
	}

	{
		cout << "with empty domain will be error\n";
		cout << "\"\", \"/document.doc\", HTTP, 80" << endl;
		REQUIRE_THROWS(CHttpUrl("", "/document.doc", Protocol::HTTP, 80));
		cout << "Done\n\n";
	}

	{
		cout << "domain with forbidden symbol \"№\" call error \n";
		cout << "www.mysite№.com, \"\", HTTP, 80" << endl;
		REQUIRE_THROWS(CHttpUrl("www.mysite№.com", "", Protocol::HTTP, 80));
		cout << "Done\n\n";
	}
}
