#include <iostream>
#include <string>
#include <regex>
#include "ParserFuncs.h"

using namespace std;

const string ENT_URL = "Enter URL. To stop the process enter \"stop\". \n";
const string INC_URL = "This URL doesn\'t correct\n";

int main()
{
    cout << ENT_URL << endl;
    string url;
    while (getline(cin, url) && url != "stop") 
    {
        Protocol protocol;
        int port;
        string host;
        string document;
        if (ParseURL(url, protocol, port, host, document))
        {
            PrintParsedURL(protocol, port, host, document);
        }
        else
        {
            cout << INC_URL;
        }
        cout << endl << endl;
    }
    return 0;
}