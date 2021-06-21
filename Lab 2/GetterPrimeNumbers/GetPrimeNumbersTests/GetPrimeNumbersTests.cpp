#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../GetterPrimeNumbers/FuncsGetPrimes.h"

SCENARIO("GeneratePrimeNumbersSet: upperBound < 0")
{
	cout << "GeneratePrimeNumbersSet: upperBound < 0" << endl;
	std::set<int> set;
	int upperBound = -100;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 0);
	cout << "Done" << endl;
}

SCENARIO("GeneratePrimeNumbersSet: upperBound = 0")
{
	cout << "GeneratePrimeNumbersSet: upperBound = 0" << endl;
	std::set<int> set;
	int upperBound = 0;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 0);
	cout << "Done" << endl;
}

SCENARIO("GeneratePrimeNumbersSet: upperBound > 0")
{
	cout << "GeneratePrimeNumbersSet: upperBound > 0" << endl;
	std::set<int> set;
	int upperBound = 10;
	set = GeneratePrimeNumbersSet(upperBound);
	std::set<int> expectingSet{ 1, 2, 3, 5, 7 };
	REQUIRE(set == expectingSet);
	cout << "Done" << endl;
}

SCENARIO("GeneratePrimeNumbersSet: upperBound > 100000000")
{
	cout << "GeneratePrimeNumbersSet: upperBound > 100000000" << endl;
	std::set<int> set;
	int upperBound = 100000001;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 0);
	cout << "Done" << endl;
}

