#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../BodyStreamHandler/BodyStreamHandler.h"
#include "../geomaBodies/CBody.h"
#include "../geomaBodies/CCone.h"
#include "../geomaBodies/CCylinder.h"
#include "../geomaBodies/CParallelepiped.h"
#include "../geomaBodies/CSphere.h"

using namespace std;

SCENARIO("Valid sphere creation")
{
	cout << "Valid sphere creation" << endl;
	CSphere sphere = CSphere(15, 10);
	REQUIRE(sphere.GetDensity() == 15);
	REQUIRE(sphere.GetRadius() == 10);
	cout << "Done" << endl << endl;
}

SCENARIO("Valid cone creation")
{
	cout << "Valid cone creation" << endl;
	CCone cone(13.5, 13.7, 111.1);
	REQUIRE(cone.GetDensity() == 13.5);
	REQUIRE(cone.GetBaseRadius() == 13.7);
	REQUIRE(cone.GetHeight() == 111.1);
	cout << "Done" << endl << endl;
}

SCENARIO("Valid cylinder creation")
{
	cout << "Valid cylinder creation" << endl;
	CCylinder cylinder(90.1, 57.7, 62.0);
	REQUIRE(cylinder.GetDensity() == 90.1);
	REQUIRE(cylinder.GetBaseRadius() == 57.7);
	REQUIRE(cylinder.GetHeight() == 62.0);
	cout << "Done" << endl << endl;
}

SCENARIO("Valid parallelepiped creation")
{
	cout << "Valid parallelepiped creation" << endl;
	CParallelepiped parallelepiped(1.1, 999.3, 5, 7.439);
	REQUIRE(parallelepiped.GetDensity() == 1.1);
	REQUIRE(parallelepiped.GetWidth() == 999.3);
	REQUIRE(parallelepiped.GetDepth() == 5);
	REQUIRE(parallelepiped.GetHeight() == 7.439);
	cout << "Done" << endl << endl;
}