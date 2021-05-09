// Vector_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../vector/VecFuncs.h"
using namespace std;
using Vector = vector<float>;


SCENARIO("Test with simple vector")
{
	cout << "Test with simple vector\n";
	Vector realityVec = { 5, 10, 5, 10 };
	MultiplyMaxDivideMinimum(realityVec);
	Vector expectedVec = { 10, 20, 10, 20 };
	REQUIRE(realityVec == expectedVec);
}

SCENARIO("Test with negative numbers")
{
	cout << "Test with negative numbers\n";
	Vector realityVec = { -5, 10, 5, 10 };
	MultiplyMaxDivideMinimum(realityVec);
	Vector expectedVec = { 10, -20, -10, -20 };
	REQUIRE(realityVec == expectedVec);
}

SCENARIO("Test with empty vector")
{
	cout << "Test with empty vector\n";
	Vector realityVec(0);
	MultiplyMaxDivideMinimum(realityVec);
	Vector expectedVec (0);
	REQUIRE(realityVec == expectedVec);
}

SCENARIO("Test with the element equal 0")
{
	cout << "Test with the element equal 0\n";
	Vector realityVec = {12, 0, 1};
	MultiplyMaxDivideMinimum(realityVec);
	Vector expectedVec = { 12, 0, 1 };
	REQUIRE(realityVec == expectedVec);
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

