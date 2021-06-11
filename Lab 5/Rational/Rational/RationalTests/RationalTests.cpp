﻿#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Rational/CRational.h"

using namespace std;

SCENARIO("Valid sphere creation")
{
	CRational rat = CRational(1, 3);
	CRational rat2 = CRational(2, 1);
	CRational rat3 = CRational();
	rat3 += rat2;
	REQUIRE(rat3.GetNumerator() == 2);
	REQUIRE(rat3.GetDenominator() == 1);
}

SCENARIO("Constructors")
{
	cout << "Constructors" << endl << endl;
	cout << "default constructor" << endl;
	CRational ratDefault;
	REQUIRE((ratDefault.GetNumerator() == 0 && ratDefault.GetDenominator() == 1));
	
	cout << "constructor with one argument" << endl;
	CRational rat1(-10);
	REQUIRE((rat1.GetNumerator() == -10 && rat1.GetDenominator() == 1));

	cout << "constructor with two arguments" << endl;
	CRational rat2(10, 5);
	REQUIRE((rat2.GetNumerator() == 2 && rat2.GetDenominator() == 1));
		
	CRational rat3(-10, 5);
	REQUIRE((rat3.GetNumerator() == -2 && rat3.GetDenominator() == 1));

	REQUIRE_THROWS(CRational(-10, -5));
	cout << "Done" << endl << endl;
}

SCENARIO("comparison operators") 
{
	cout << "equality operators" << endl;
	cout << "==" << endl;
	WHEN("1/7 and 1/7") 
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 == rat2) == true);
	}
	WHEN("2/1 and 2")
	{
		CRational rat1(2, 1);
		CRational rat2(2);
		REQUIRE((rat1 == rat2) == true);
	}

	WHEN("4/2 and 2/1")
	{
		CRational rat1(4, 2);
		CRational rat2(2, 1);
		REQUIRE((rat1 == rat2) == true);
	}

	cout << "!=" << endl;
	WHEN("1/7 and 1/8")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 != rat2) == true);
	}
	
	cout << ">=" << endl;
	WHEN("1/7 and 1/8")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 >= rat2) == true);
	}

	WHEN("1/7 and 1/7")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 >= rat2) == true);
	}

	WHEN("1/8 and 1/7")
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 >= rat2) == false);
	}
	cout << "<=" << endl;
	WHEN("1/7 and 1/8")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 <= rat2) == false);
	}

	WHEN("1/7 and 1/7")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 <= rat2) == true);
	}

	WHEN("1/8 and 1/7")
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 <= rat2) == true);
	}

	cout << "<" << endl;
	WHEN("1/8 and 1/7")
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 < rat2) == true);
	}

	WHEN("1/7 and 1/7")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 < rat2) == false);
	}

	WHEN("1/7 and 1/8")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 < rat2) == false);
	}

	cout << ">" << endl;
	WHEN("1/8 and 1/7")
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 > rat2) == false);
	}

	WHEN("1/7 and 1/7")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 > rat2) == false);
	}

	WHEN("1/7 and 1/8")
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 > rat2) == true);
	}
}

SCENARIO("Binary operators") 
{
	cout << "Binary operators" << endl << endl;
	cout << "+=" << endl;
	WHEN("1/5 and 2/5") 
	{
		CRational rat1(1, 5);
		CRational rat2(2, 5);
		CRational expecRat(3, 5);
		rat1 += rat2;
		REQUIRE(rat1 == expecRat);
	}

	WHEN("10/1 and 1")
	{
		CRational rat1(10, 1);
		CRational rat2(1);
		CRational expecRat(11, 1);
		rat1 += rat2;
		REQUIRE(rat1 == expecRat);
	}

	WHEN("1 and 10/1")
	{
		CRational rat1(1);
		CRational rat2(10/1);
		CRational expecRat(11, 1);
		rat1 += rat2;
		REQUIRE(rat1 == expecRat);
	}

	cout << "-=" << endl;
	WHEN("1/5 and 2/5")
	{
		CRational rat1(1, 5);
		CRational rat2(2, 5);
		CRational expecRat(-1, 5);
		rat1 -= rat2;
		REQUIRE(rat1 == expecRat);
	}

	WHEN("10/1 and 1")
	{
		CRational rat1(10, 1);
		CRational rat2(1);
		CRational expecRat(9, 1);
		rat1 -= rat2;
		REQUIRE(rat1 == expecRat);
	}

	WHEN("1 and 10/1")
	{
		CRational rat1(1);
		CRational rat2(10 / 1);
		CRational expecRat(-9, 1);
		rat1 -= rat2;
		REQUIRE(rat1 == expecRat);
	}

	cout << "*=" << endl;
	WHEN("1/5 and 2/5")
	{
		CRational rat1(1, 5);
		CRational rat2(2, 5);
		CRational expecRat(2, 25);
		rat1 *= rat2;
		REQUIRE(rat1 == expecRat);
	}

	WHEN("10/2 and 2")
	{
		CRational rat1(10, 2);
		CRational rat2(2);
		CRational expecRat(20, 2);
		rat1 *= rat2;
		REQUIRE(rat1 == expecRat);
	}

	WHEN("2 and 10/2")
	{
		CRational rat1(2);
		CRational rat2(10, 2);
		CRational expecRat(20, 2);
		rat1 *= rat2;
		REQUIRE(rat1 == expecRat);
	}

	cout << "/=" << endl;
	WHEN("1/5 and 0/5")
	{
		CRational rat1(1, 5);
		CRational rat2(0, 5);
		REQUIRE_THROWS(rat1 /= rat2);
	}

	WHEN("10/2 and 2")
	{
		CRational rat1(10, 2);
		CRational rat2(2);
		CRational expecRat(10, 4);
		rat1 /= rat2;
		REQUIRE(rat1 == expecRat);
	}

	WHEN("2/10 and 10/2")
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(4, 100);
		rat1 /= rat2;
		REQUIRE(rat1 == expecRat);
	}

	cout << "+" << endl;
	WHEN("2/10 and 10/2")
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(104, 20);
		REQUIRE(rat1 + rat2 == expecRat);
	}

	WHEN("2/10 and 10")
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(102, 10);
		REQUIRE(rat1 + rat2 == expecRat);
	}

	cout << "-" << endl;
	WHEN("2/10 and 10/2")
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(-96, 20);
		REQUIRE(rat1 - rat2 == expecRat);
	}

	WHEN("2/10 and 10")
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(-98, 10);
		REQUIRE(rat1 - rat2 == expecRat);
	}

	cout << "*" << endl;
	WHEN("2/10 and 10/2")
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(20, 20);
		REQUIRE(rat1 * rat2 == expecRat);
	}

	WHEN("2/10 and 10")
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(20, 10);
		REQUIRE(rat1 * rat2 == expecRat);
	}

	cout << "/" << endl;
	WHEN("2/10 and 10/2")
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(4, 100);
		REQUIRE(rat1 / rat2 == expecRat);
	}

	WHEN("2/10 and 10")
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(2, 100);
		REQUIRE(rat1 / rat2 == expecRat);
	}

	WHEN("2/10 and 0/1")
	{
		CRational rat1(2, 10);
		CRational rat2;
		REQUIRE_THROWS(rat1 / rat2);
	}
}

SCENARIO("unary operations")
{
	cout << "-" << endl;
	WHEN("2/10")
	{
		CRational rat1(2, 10);
		CRational expecRat(-2, 10);
		REQUIRE(-rat1 == expecRat);
	}

	cout << "+" << endl;
	WHEN("2/10")
	{
		CRational rat1(2, 10);
		CRational expecRat(2, 10);
		REQUIRE(+rat1 == expecRat);
	}
}

SCENARIO("input and output operations") 
{

}