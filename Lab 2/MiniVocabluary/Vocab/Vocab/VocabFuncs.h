#pragma once
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

bool checkQuantity(int argc);
std::string Lower(std::string str);
bool getAnswer();
void Initialize(std::ifstream& inFile, VocabMap& voc);
void PrintSet(SetString values);
bool UserActionHandler(VocabMap& vocabluary);
void PrintMapInFile(std::ofstream& outFile, VocabMap vocabulary);