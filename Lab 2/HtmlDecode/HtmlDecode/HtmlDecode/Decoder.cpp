#include <iostream>
#include <string>
#include <map>

using namespace std;
using Iterator = map<string, string>::iterator;

const string ENT_HTML_CODE = "Enter a string with html code\n";
const int NOT_FOUD = string::npos;

string ReplaceStr(string line, string searchString, string replaceString)
{
	string result;
	size_t startingPosition = 0;
	while (line.find(searchString) != NOT_FOUD)
	{
		startingPosition = line.find(searchString);
		line.replace(startingPosition, searchString.length(), replaceString);
		result.insert(result.length(), line.substr(0, startingPosition + replaceString.length()));
		line.erase(0, startingPosition + (replaceString).length());
	}
	result.insert(result.length(), line);
	return result;
};

string HtmlDecode(string const& html)
{
	string decodedHtml = html;
	map<string, string> values = { {"&quot;", "\""},
										 {"&apos;", "\'"},
										 {"&lt;", "<"},
										 {"&gt;", ">"},
										 {"&amp;", "&"}
	};
	for (Iterator iterator = values.begin(); iterator != values.end(); iterator++)
	{
		decodedHtml = ReplaceStr(decodedHtml, iterator->first, iterator->second);
	}
	return decodedHtml;
}