#pragma once
#include <string>
#include "CUrlParsingError.h"

using namespace std;

enum class Protocol
{
	HTTP,
	HTTPS,
	WITHOUT_PROTOCOL
};


class CHttpUrl
{
public:
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(string const& url);///////////

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		string const& domain,
		string const& document,
		Protocol protocol = Protocol::HTTP);///////////////////

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		string const& domain,
		string const& document,
		Protocol protocol,
		unsigned short port);//////////////////////////

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
	// не должен включатьс€
	string GetURL() ;

	// возвращает доменное им€
	string GetDomain() const;

	/*
		¬озвращает им€ документа. ѕримеры:
			/
			/index.html
			/images/photo.jpg
	*/
	string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
	unsigned short GetPort() const;

	string ProtocolString() const;

private:
	Protocol GetProtocolFromRequest(string protocolStr) const;
	unsigned short GetPortFromRequest(string portStr) const;
	bool isCorrectProtocol() const;
	bool isCorrectDomain() const;
	bool isCorrectPort() const;
	void addMissingSlash(string& document);
	string FilterPort();


	string m_url;
	Protocol m_protocol;
	string m_domain;
	unsigned short m_port;
	string m_document;
};

