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
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(string const& url);///////////

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		string const& domain,
		string const& document,
		Protocol protocol = Protocol::HTTP);///////////////////

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		string const& domain,
		string const& document,
		Protocol protocol,
		unsigned short port);//////////////////////////

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
	// �� ������ ����������
	string GetURL() ;

	// ���������� �������� ���
	string GetDomain() const;

	/*
		���������� ��� ���������. �������:
			/
			/index.html
			/images/photo.jpg
	*/
	string GetDocument() const;

	// ���������� ��� ���������
	Protocol GetProtocol() const;

	// ���������� ����� �����
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

