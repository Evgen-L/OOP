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

SCENARIO("Valid print")
{
	cout << "Valid max mass body print" << endl;
	stringstream input;
	stringstream output1;
	stringstream output2;
	stringstream output3;

	stringstream expOutput1;
	stringstream expOutput2;
	stringstream expOutput3;

	input << "Cylinder 10 20 10" << endl;
	input << "Cylinder 10 20 5" << endl;


	expOutput1 << "Cylinder:"<<endl
		<< "\tdensity = " << "10" << endl
		<< "\tvolume = " << "12566.37061" << endl
		<< "\tmass = " << "125663.7061" << endl
		<< "\tradius = " << "20" << endl
		<< "\theight = " << "10" << endl << endl;

	expOutput1 << "Cylinder:" << endl
		<< "\tdensity = " << "10" << endl
		<< "\tvolume = " << "6283.185307" << endl
		<< "\tmass = " << "62831.85307" << endl
		<< "\tradius = " << "20" << endl
		<< "\theight = " << "5" << endl << endl;

	expOutput2  << "The body with max mass:" << endl <<
		"Cylinder:" << endl
		<< "\tdensity = " << "10" << endl
		<< "\tvolume = " << "12566.37061" << endl
		<< "\tmass = " << "125663.7061" << endl
		<< "\tradius = " << "20" << endl
		<< "\theight = " << "10" << endl << endl;

	expOutput3 << "Lightest body in water:" << endl <<
		"Cylinder:" << endl
		<< "\tdensity = " << "10" << endl
		<< "\tvolume = " << "6283.185307" << endl
		<< "\tmass = " << "62831.85307" << endl
		<< "\tradius = " << "20" << endl
		<< "\theight = " << "5" << endl << endl;

	BodyStreamHandler handler;
	handler.ReadBodies(input);
	handler.PrintBodiesInfo(output1);
	handler.PrintMaxMassBody(output2);
	handler.PrintLightestBodyInWater(output3);
	REQUIRE(output1.str() == expOutput1.str());
	REQUIRE(output2.str() == expOutput2.str());
	REQUIRE(output3.str() == expOutput3.str());
	
	cout << "Done" << endl << endl;
}

SCENARIO("Valid search max mass and lightest bodies") 
{
	cout << "Valid search max mass and lightest bodies" << endl;

	stringstream input;
	input << "Cylinder 10 20 10" << endl;
	input << "Cylinder 10 20 5" << endl;

	vector<unique_ptr<CBody>> vectorWithOneBody1;
	vector<unique_ptr<CBody>> vectorWithOneBody2;
	vectorWithOneBody1.push_back(make_unique<CCylinder>(10, 20, 10));
	vectorWithOneBody2.push_back(make_unique<CCylinder>(10, 20, 5));

	vector <unique_ptr< CBody>>::const_iterator expMaxMassBody = std::max_element(vectorWithOneBody1.begin(), vectorWithOneBody1.end(), [](unique_ptr<CBody> const& a, unique_ptr<CBody> const& b)
		{
			return (*a).GetMass() < (*b).GetMass();
		}
	);
	vector <unique_ptr< CBody>>::const_iterator expLightesBody = min_element(vectorWithOneBody2.begin(), vectorWithOneBody2.end(), [](unique_ptr<CBody> const& a, unique_ptr<CBody> const& b)
		{
			return (*a).GetWeightInWater() < (*b).GetWeightInWater();
		}
	);
	
	BodyStreamHandler handler;
	handler.ReadBodies(input);
	
	REQUIRE((*handler.GetInfoMaxMassBody())->ToString() == (*expMaxMassBody)->ToString());
	REQUIRE((*handler.GetInfoLightestBodyInWater())->ToString() == (*expLightesBody)->ToString());

	cout << "Done" << endl << endl;
}