#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <clocale>
#include <sstream>
#include <algorithm>

using VocabMap = std::map <std::string, std::set<std::string>>;
using SetString = std::set <std::string>;

const std::string MUST_ONE = "There must be 1 argument\n";
const std::string UNKNOW_WORD = "����������� �����";
const std::string TRANSLATION_OR_EMPTY_STRING = "������� ������� ��� ������ ������ ��� ������.\n";
const std::string THE_WORD = "����� ";
const std::string SAVED_IN_VOCABULARY_AS = "��������� � ������� ���";
const std::string IGNORED = "���������������";

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
	while (getline(std::cin, YesNo) && Lower(YesNo) != Lower("Yes") && YesNo != Lower("No")) {}
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
		//�������� �������
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