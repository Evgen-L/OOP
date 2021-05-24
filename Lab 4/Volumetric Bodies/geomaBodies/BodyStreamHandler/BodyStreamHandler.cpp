#include "BodyStreamHandler.h"
#include <map>
#include <sstream>

using namespace std;


const map<string, Bodies> bodies_storage = {
	{"Cylinder", Bodies::CYLINDER},
	{ "Cone", Bodies::CONE},
	{ "Parallelepiped", Bodies::PARALLELEPIPED},
	{ "Sphere", Bodies::SPHERE}
};

//const string ENTER_NUMBER_BODIES = "Please enter number of bodies\n";
const string INCORRECT_FORMAT = "Incorrect format\n\n";
const string INCORRECT_NAME_BODY_FORMAT = "Incorrect name body format\n\n";
const string INCORRECT_PARAMETERS_BODY_FORMAT = "Incorrect name body format\n\n";
const string INCORRECT_VALUES_PARAMETERS = "Incorrect values of parameters\n\n";

bool BodyStreamHandler::isPositiveNumbers(vector<double> numbers) const
{
	for (int i = 0; i < numbers.size(); i++)
	{		
		if (numbers[i] > 0)
		{		
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool BodyStreamHandler::GetBody(stringstream& streamUserInput, Bodies& body)
{
	string nameBody;
	streamUserInput >> nameBody;
	if (bodies_storage.find(nameBody) != bodies_storage.end()) 
	{
		body = bodies_storage.at(nameBody);
		return true;
	}
	return false;
}

bool BodyStreamHandler::PushCylinderInVector(stringstream& parameters)
{
	double density = 0;
	double radius = 0;
	double height = 0;

	if (parameters >> density && parameters >> radius && parameters >> height)
	{
		vector<double>numbers = { density , radius, height };
		if (isPositiveNumbers(numbers))
		{
			m_bodies.push_back(make_unique<CCylinder>(density, radius, height));
			return true;
		}
	}
	return false;
}

bool BodyStreamHandler:: PushConeInVector(stringstream& parameters)
{
	double density = 0;
	double radius = 0;
	double height = 0;

	if (parameters >> density && parameters >> radius && parameters >> height)
	{
		if (isPositiveNumbers({ density , radius, height }))
		{
			m_bodies.push_back(make_unique<CCone>(density, radius, height));
			return true;
		}
	}
	return false;
}

bool BodyStreamHandler::PushParallelepipedInVector(stringstream& parameters)
{
	double density;  
	double width; 
	double depth; 
	double height;

	if (parameters >> density && parameters >> width && parameters >> depth && parameters >> height)
	{
		if (isPositiveNumbers({density, width, depth, height}))
		{
			m_bodies.push_back(make_unique<CParallelepiped>(density, width, depth, height));
			return true;
		}
	}
	return false;
}

bool BodyStreamHandler::PushSphereInVector(stringstream& parameters)
{
	double density;
	double radius;

	if (parameters >> density && parameters >> radius)
	{
		if (isPositiveNumbers({ density , radius }))
		{
			m_bodies.push_back(make_unique<CSphere>(density, radius));
			return true;
		}
	}
	return false;
}


void BodyStreamHandler::SwitchBodyToPushInVector(Bodies& nameBody, stringstream& paramsBody)
{
	switch (nameBody)
	{
	case Bodies::CYLINDER:
		if (!PushCylinderInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
		}
		break;

	case Bodies::CONE:
		if (!PushConeInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
		}
		break;

	case Bodies::PARALLELEPIPED:
		if (!PushParallelepipedInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
		}
		break;

	case Bodies::SPHERE:
		if (!PushSphereInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
		}
		break;
	default:
		break;
	}
}

bool BodyStreamHandler::PushBodyInVector(stringstream& paramsBody, Bodies& nameBody)
{
	if (!(nameBody == Bodies::NONE)) 
	{
		SwitchBodyToPushInVector(nameBody, paramsBody);
		return true;
	}
	return false;
}

BodyStreamHandler::BodyStreamHandler() 
{
}


void BodyStreamHandler::PrintBodiesInfo() const
{
	
	for (auto const& pointerBody  : m_bodies)
	{
		cout << pointerBody->ToString() << endl;
	}
}

void BodyStreamHandler::ReadBodies() 
{
	
	/*cout << ENTER_NUMBER_BODIES;
	int numberBodies = 0;
	while (!(cin >> numberBodies))
		cout << INCORRECT_FORMAT;
	*/
	string userInput;
	while (getline(cin, userInput))
	{
		//cout << "userInput:  " << userInput << endl;
		stringstream streamUserInput(userInput);
		//cout << streamUserInput.str();
		Bodies nameBody = Bodies::NONE;
		if (!GetBody(streamUserInput, nameBody))
		{
			cout << INCORRECT_NAME_BODY_FORMAT;
			continue;
		}
		if (!PushBodyInVector(streamUserInput, nameBody)) 
		{
			cout << INCORRECT_PARAMETERS_BODY_FORMAT;
			continue;
		}
	}
}