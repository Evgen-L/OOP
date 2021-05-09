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

using VocabMap = std::map <std::string, std::set<std::string>>;
using SetString = std::set <std::string>;

const std::string MUST_ONE = "There must be 1 argument\n";
const std::string DICTIONARY_NOT_FOUND= "File - Dictionary not found. Do you want to create it at the end of the work? (Yes / No)\n";
const std::string UNKNOW_WORD = "Неизвестное слово";
const std::string TRANSLATION_OR_EMPTY_STRING = "Введите перевод или пустую строку для отказа.\n";
const std::string THE_WORD = "Слово ";
const std::string SAVED_IN_VOCABULARY_AS = "сохранено в словаре как";
const std::string IGNORED = "проигнорировано";
const std::string CHANGES_IN_FILE = "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";

bool checkQuantity(int argc)
{
	if (argc != 2)
	{
		std::cout << MUST_ONE;
		return false;
	}
	return true;
}

std::string Lower(std::string str) 
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

bool getAnswer()
{
	std::string YesNo;
	while (getline(std::cin, YesNo) && Lower(YesNo) != Lower("Yes") && YesNo != Lower("No")){}
	system("cls");
	if (Lower(YesNo) == Lower("Yes")) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Initialize(std::ifstream& inFile, VocabMap& voc) 
{
	std::string line;
	while (getline(inFile, line)) 
	{
		std::string key;
		std::string word;
		std::stringstream stringStream(line);

		while (stringStream >> word && word != "=")
		{
			key += word;
		}

		SetString values;
		std::string value;
		while (stringStream >> word)
		{
			if (!(word == "/")) 
			{
				value += word + " ";
			}
			else 
			{
				value.erase(value.size() - 1);
				values.insert(Lower(value));
				value = "";
			}
		}
		value.erase(value.size() - 1);
		values.insert(Lower(value));
		voc[Lower(key)] = values;
		//обратный перевод
		SetString keyValue;
		keyValue.insert(Lower(key));
		for (std::string value : values) 
		{
			if (voc.count(value) == 1) 
			{
				VocabMap::iterator it = voc.find(value);
				it->second.insert(Lower(key));
			}
			else 
			{
				voc[value] = keyValue;
			}
		}
	}
}


void PrintSet(SetString values)
{
	for (std::string value : values)
	{
		std::cout << value + " ";
	}
	std::cout << std::endl;
}

bool UserActionHandler(VocabMap& vocabluary) 
{
	bool isChanges = false;
	std::string collocation;
	while (getline(std::cin, collocation) && collocation != "...")
	{
		std::string lowerCollocation = Lower(collocation);
		if (vocabluary.count(lowerCollocation) == 1)
		{
			VocabMap::iterator it = vocabluary.find(lowerCollocation);
			PrintSet(it->second);
			std::cout << std::endl;
		}
		else 
		{
			std::cout << UNKNOW_WORD << " \"" + collocation + "\". " << TRANSLATION_OR_EMPTY_STRING;
			std::string translate;
			getline(std::cin, translate);
			if (!translate.empty()) 
			{
				isChanges = true;
				std::cout << THE_WORD << " \"" + collocation + "\" " << SAVED_IN_VOCABULARY_AS << " \"" + translate + "\" " << std::endl;
				std::string lowerTranslate = Lower(translate);
				vocabluary[lowerCollocation] = SetString{ lowerTranslate };
				if (vocabluary.count(lowerTranslate) == 1)
				{
					VocabMap::iterator it = vocabluary.find(lowerTranslate);
					it->second.insert(lowerCollocation);
				}
				else
				{
					SetString setCollocation;
					setCollocation.insert(lowerCollocation);
					vocabluary[lowerTranslate] = setCollocation;
				}
			}
			else 
			{
				std::cout << THE_WORD << " \"" + collocation + "\" " << IGNORED << std::endl;
			}
		}
	}
	if (isChanges) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PrintMapInFile(std::ofstream& outFile, VocabMap vocabulary)
{
	for (VocabMap::iterator vocabularyIterator = vocabulary.begin(); vocabularyIterator != vocabulary.end(); vocabularyIterator++)
	{
		short count = 0;
		outFile << vocabularyIterator->first << " = ";
		for (std::string value : vocabularyIterator->second)
		{
			if (count == 0)
			{
				outFile << value;
			}
			else
			{
				outFile << " / " + value;
			}
			count++;
		}
		outFile << std::endl;
	}
}

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