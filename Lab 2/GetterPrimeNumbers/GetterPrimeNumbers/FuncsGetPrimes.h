#pragma once
#include <set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<bool> GetPrimeNumbersList(int upperBound);
set<int> GeneratePrimeNumbersSet(int upperBound);
void printSet(set<int> set);