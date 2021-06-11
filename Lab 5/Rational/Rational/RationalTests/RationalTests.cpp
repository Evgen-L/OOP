#include <iostream>
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
	cout << "Done" << endl << endl;

	cout << "constructor with one argument" << endl;
	CRational rat1(-10);
	REQUIRE((rat1.GetNumerator() == -10 && rat1.GetDenominator() == 1));
	cout << "Done" << endl << endl;

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
	cout << "equality operators" << endl << endl;
	cout << "==" << endl;
	
	cout << "1/7 == 1/7" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 == rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "2/1 == 2" << endl;
	{
		CRational rat1(2, 1);
		CRational rat2(2);
		REQUIRE((rat1 == rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "4/2 == 2/1" << endl;
	{
		CRational rat1(4, 2);
		CRational rat2(2, 1);
		REQUIRE((rat1 == rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "!=" << endl;
	cout << "1/7 != 1/8" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 != rat2) == true);
		cout << "Done" << endl << endl;
	}
	
	cout << ">=" << endl;
	cout << "1/7 >= 1/8" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 >= rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "1/7 >= 1/7" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 >= rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "1/8 !>= 1/7" << endl;
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 >= rat2) == false);
		cout << "Done" << endl << endl;
	}

	cout << "<=" << endl;
	cout << "1/7 !<= 1/8" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 <= rat2) == false);
		cout << "Done" << endl << endl;
	}

	cout << "1/7 <= 1/7" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 <= rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "1/8 <= 1/7" << endl;
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 <= rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "<" << endl;
	cout << "1/8 < 1/7" << endl;
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 < rat2) == true);
		cout << "Done" << endl << endl;
	}

	cout << "1/7 !< 1/7" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 < rat2) == false);
		cout << "Done" << endl << endl;
	}

	cout << "1/7 !< 1/8" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 < rat2) == false);
		cout << "Done" << endl << endl;
	}

	cout << ">" << endl;
	cout << "1/8 !> 1/7" << endl;
	{
		CRational rat1(1, 8);
		CRational rat2(1, 7);
		REQUIRE((rat1 > rat2) == false);
		cout << "Done" << endl << endl;
	}

	cout << "1/7 ! > 1/7" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 7);
		REQUIRE((rat1 > rat2) == false);
		cout << "Done" << endl << endl;
	}

	cout << "1/7 > 1/8" << endl;
	{
		CRational rat1(1, 7);
		CRational rat2(1, 8);
		REQUIRE((rat1 > rat2) == true);
		cout << "Done" << endl << endl;
	}
}

SCENARIO("Binary operators") 
{
	cout << "Binary operators" << endl << endl;
	cout << "+=" << endl;	
	{
		cout << "4/5 and 1/5 to be 1/1" << endl;
		CRational rat1(4, 5);
		CRational rat2(1, 5);
		CRational expecRat(1, 1);
		rat1 += rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}
	{
		cout << "1/5 and 2/5 to be 3/5" << endl;
		CRational rat1(1, 5);
		CRational rat2(2, 5);
		CRational expecRat(3, 5);
		rat1 += rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}
	
	cout << "10/1 and 1 to be 11/1" << endl;
	{
		CRational rat1(10, 1);
		CRational rat2(1);
		CRational expecRat(11, 1);
		rat1 += rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "1 and 10/1 to be 11/1" << endl;
	{
		CRational rat1(1);
		CRational rat2(10/1);
		CRational expecRat(11, 1);
		rat1 += rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "-=" << endl;
	cout << "1/5 and 2/5 to be -1/5" << endl;
	{
		CRational rat1(1, 5);
		CRational rat2(2, 5);
		CRational expecRat(-1, 5);
		rat1 -= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "10/1 and 1 to be 9/1" << endl;
	{
		CRational rat1(10, 1);
		CRational rat2(1);
		CRational expecRat(9, 1);
		rat1 -= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "1 and 10/1 to be -9/1" << endl;
	{
		CRational rat1(1);
		CRational rat2(10 / 1);
		CRational expecRat(-9, 1);
		rat1 -= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "*=" << endl;
	cout << "1/5 and 2/5 to be 2/25" << endl;
	{
		CRational rat1(1, 5);
		CRational rat2(2, 5);
		CRational expecRat(2, 25);
		rat1 *= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "10/2 and 2 to be 10/1" << endl;
	{
		CRational rat1(10, 2);
		CRational rat2(2);
		CRational expecRat(10, 1);
		rat1 *= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "2 and 10/2 to be 10/1" << endl;
	{
		CRational rat1(2);
		CRational rat2(10, 2);
		CRational expecRat(20, 2);
		rat1 *= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "/=" << endl;
	cout << "1/5 and 0/5 to be error" << endl;
	{
		CRational rat1(1, 5);
		CRational rat2(0, 5);
		REQUIRE_THROWS(rat1 /= rat2);
		cout << "Done" << endl << endl;
	}

	cout << "10/2 and 2 to be 5/2" << endl;
	{
		CRational rat1(10, 2);
		CRational rat2(2);
		CRational expecRat(5, 2);
		rat1 /= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "2/10 and 10/2 to be 1/25" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(1, 25);
		rat1 /= rat2;
		REQUIRE(rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "+" << endl;
	cout << "2/10 and 10/2 to be 26/5" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(26, 5);
		REQUIRE(rat1 + rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "2/10 and 10 to be 51/5" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(51, 5);
		REQUIRE(rat1 + rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "-" << endl;
	cout << "2/10 and 10/2 to be -24/5" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(-24, 5);
		REQUIRE(rat1 - rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "2/10 and 10 to be -49/5" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(-49, 5 );
		REQUIRE(rat1 - rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "*" << endl;
	cout << "2/10 and 10/2 to be 1/1" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(1, 1);
		REQUIRE(rat1 * rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "2/10 and 10 to be 2/1" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(2, 1);
		REQUIRE(rat1 * rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "/" << endl;
	cout << "2/10 and 10/2 to be 1/25" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10, 2);
		CRational expecRat(1, 25);
		REQUIRE(rat1 / rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "2/10 and 10 to be 1/50" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2(10);
		CRational expecRat(1, 50);
		REQUIRE(rat1 / rat2 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "2/10 and 0/1 to be error" << endl;
	{
		CRational rat1(2, 10);
		CRational rat2;
		REQUIRE_THROWS(rat1 / rat2);
		cout << "Done" << endl << endl;
	}
}

SCENARIO("unary operations")
{
	cout << "unary operations" << endl << endl;
	cout << "-" << endl;
	cout << "- 3/10 to be -3/10" << endl;
	{
		CRational rat1(3, 10);
		CRational expecRat(-3, 10);
		REQUIRE(-rat1 == expecRat);
		cout << "Done" << endl << endl;
	}

	cout << "+" << endl;
	cout << "+3/10 to be 3/10" << endl;
	{
		CRational rat1(3, 10);
		CRational expecRat(3, 10);
		REQUIRE(+rat1 == expecRat);
		cout << "Done" << endl << endl;
	}
}

SCENARIO("input and output operations") 
{
	{
		cout << "<<" << endl;
		cout << "stringRat << 9/10" << endl;
		ostringstream stringRat;
		CRational rat(9, 10);
		stringRat << rat;
		REQUIRE(stringRat.str() == "9/10");
		cout << "Done" << endl << endl;
	}
	

	{
		cout << ">>" << endl;
		cout << "stringRat >> rat. rat to be 9/10" << endl;
		istringstream stringRat("9/10");
		CRational rat;
		stringRat >> rat;
		CRational expecRat(9, 10);
		REQUIRE(rat == expecRat);
		cout << "Done" << endl << endl;
	}

	{
		cout << "stringRat >> rat. stringRat = ./10 To be error" << endl;
		istringstream stringRat("./10");
		CRational rat;
		REQUIRE_THROWS(stringRat >> rat);
		cout << "Done" << endl << endl;
	}

	{
		cout << "stringRat >> rat. stringRat = 9+10.To be error" << endl;
		istringstream stringRat("9+10");
		CRational rat;
		REQUIRE_THROWS(stringRat >> rat);
		cout << "Done" << endl << endl;
	}

	{
		cout << "stringRat >> rat1. rat1 to be 9/10. stringRat >> rat2. rat2 to be 8/11 " << endl;
		istringstream stringRat("9/10 8/11");
		CRational rat1;
		CRational rat2;
		stringRat >> rat1;
		stringRat >> rat2;
		CRational expecRat1(9, 10);
		CRational expecRat2(8, 11);
		REQUIRE(rat1 == expecRat1);
		REQUIRE(rat2 == expecRat2);
		cout << "Done" << endl << endl;
	}
}