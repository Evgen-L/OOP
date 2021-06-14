#pragma once
#include <stdexcept>

using namespace std;

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const string& message);
}; 