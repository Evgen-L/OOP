#include <iostream> 
#include <fstream>
#include <string>
#include <optional>
#include <stdlib.h>

using namespace std;
const int NOT_FOUD = string::npos;
const string INC_INP = "Usege: Please entere correct input: <input file> <output file> <search string> <replace string>";
const string FAIL_WRITE_DATA_OUTP = "Failed to write data to output file\n";
const string NOT_READING_FILE = "Reading did not complete\n";
struct Args
{
	string inPath;
	string outPath;
	string searchString;
	string replaceString;
};

optional <Args> ParseArgv(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << INC_INP << endl;
		return nullopt;
	}
	Args args;
	args.inPath = argv[1];
	args.outPath = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

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


void CopyFile(ifstream& fromFile, ofstream& toFile) 
{
	string line;
	while (getline(fromFile, line))
	{
		toFile << line;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgv(argc, argv);
	if (!args)
	{
		return 1;
	}
	string searchString = args->searchString;
	string replaceString = args->replaceString;
	ifstream inFile;
	
	inFile.open(args->inPath);
	if (!inFile.is_open())
	{
		cout << "File '" << argv[1] << "' doesn't exist";
		return 1;
	}

	ofstream outFile;
	outFile.open(args->outPath);
	if (!outFile.is_open())
	{
		cout << "File '" << argv[2] << "' doesn't exist";
		return 1;
	}

	if (searchString == "")
	{
		CopyFile(inFile, outFile);
	}

	string line;

	while (getline(inFile, line))
	{
		string replaceLine = ReplaceStr(line, searchString, replaceString);
		
		outFile << replaceLine << endl;
		if (inFile.bad())
		{
			cout << NOT_READING_FILE;
			exit(1);
		}
	}

	if (!outFile.flush())
	{
		cout << FAIL_WRITE_DATA_OUTP;
		exit(1);
	}

	outFile.close();
	return 0;
}