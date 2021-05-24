#pragma once
#include <boost/ptr_container/ptr_vector.hpp>
#include "../geomaBodies/CBody.h"
#include "../geomaBodies/CCone.h"
#include "../geomaBodies/CCylinder.h"
#include "../geomaBodies/CParallelepiped.h"
#include "../geomaBodies/CSphere.h"

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
	BodyStreamHandler();
	void ReadBodies();
	int FindMaxMassBody(boost::ptr_vector<CBody> bodies) const;
	int FindLightestInWaterBody(boost::ptr_vector<CBody> bodies) const;
	void PrintBodiesInfo() const;

private:
	bool PushBodyInVector(stringstream& paramsBody, Bodies& nameBody);
	void SwitchBodyToPushInVector(Bodies& nameBody, stringstream& paramsBody);
	bool PushConeInVector(stringstream& parameters);
	bool PushCylinderInVector(stringstream& parameters);
	bool PushSphereInVector(stringstream& parameters);
	bool PushParallelepipedInVector(stringstream& parameters);
	bool GetBody(stringstream& streamUserInput, Bodies& body);
	bool isPositiveNumbers(vector<double> nums) const;

	vector<unique_ptr<CBody>> m_bodies;
};

