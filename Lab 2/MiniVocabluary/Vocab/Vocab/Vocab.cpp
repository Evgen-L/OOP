#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include "VocabFuncs.h"
#include <Windows.h>
#include <clocale>
#include <sstream>
#include <algorithm>

const std::string DICTIONARY_NOT_FOUND= "File - Dictionary not found. Do you want to create it at the end of the work? (Yes / No)\n";
const std::string CHANGES_IN_FILE = "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";

using VocabMap = std::map <std::string, std::set<std::string>>;
using SetString = std::set <std::string>;

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool needSave = true;
	VocabMap vocabluary;

	if (!checkQuantity(argc))
	{
		return 1;
	}

	auto inPath = argv[1];
	std::ifstream inFile;
	inFile.open(inPath);
	if (!inFile.is_open())
	{
		std::cout << DICTIONARY_NOT_FOUND;
		bool needSave = getAnswer();
	}
	else
	{
		Initialize(inFile, vocabluary);
	}

	bool isChanges = UserActionHandler(vocabluary);
	if (needSave && !inFile.is_open())
	{
		std::ofstream outFile(inPath);
		PrintMapInFile(outFile, vocabluary);
		outFile.close();
		return 0;
	}
	if (needSave && inFile.is_open())
	{
		if (isChanges) 
		{
			std::cout << CHANGES_IN_FILE;
			char ch;
			std::cin >> ch;
			if (std::tolower(ch) == 'y') 
			{
				inFile.close();
				std::remove(inPath);
				std::ofstream outFile(inPath);
				PrintMapInFile(outFile, vocabluary);
				outFile.close();
			}
		}
		return 0;
	}
	return 0;
}