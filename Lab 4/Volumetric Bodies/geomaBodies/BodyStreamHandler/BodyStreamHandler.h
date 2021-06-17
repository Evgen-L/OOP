#pragma once

#include "../geomaBodies/CBody.h"
#include "../geomaBodies/CCone.h"
#include "../geomaBodies/CCylinder.h"
#include "../geomaBodies/CParallelepiped.h"
#include "../geomaBodies/CSphere.h"

#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

enum class Bodies
{
	CYLINDER,
	CONE,
	PARALLELEPIPED,
	SPHERE,
	NONE
};

class BodyStreamHandler
{
public:
	//constructor
	BodyStreamHandler();

	//basic methods
	void ReadBodies(istream& cin);
	void PrintBodiesInfo(ostream& output) const;

	

	void PrintMaxMassBody(ostream& output) const;
	void PrintLightestBodyInWater(ostream& output) const;

	vector <unique_ptr< CBody>>::const_iterator GetInfoMaxMassBody() const;
	vector <unique_ptr< CBody>>::const_iterator GetInfoLightestBodyInWater() const;

private:
	//helpful methods
	bool PushBodyInVector(stringstream& paramsBody, Bodies& nameBody);
	bool SwitchBodyToPushInVector(Bodies& nameBody, stringstream& paramsBody);
	bool PushConeInVector(stringstream& parameters);
	bool PushCylinderInVector(stringstream& parameters);
	bool PushSphereInVector(stringstream& parameters);
	bool PushParallelepipedInVector(stringstream& parameters);
	bool GetBody(stringstream& streamUserInput, Bodies& body);
	bool isPositiveNumbers(vector<double> nums) const;

	

	//variable
	vector<unique_ptr<CBody>> m_bodies;
};