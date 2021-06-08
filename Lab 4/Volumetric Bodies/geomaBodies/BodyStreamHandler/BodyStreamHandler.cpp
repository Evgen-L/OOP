#include "BodyStreamHandler.h"


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
const string BODY_WITH_MAX_MASS = "The body with max mass:\n";
const string LIGHTEST_BODY_IN_WATER = "Lightest body in water:\n";
const string NO_BODIES_FOR_SEARCHING_MAX_MASS = "There are no bodies for searching max mass body\n\n";
const string NO_BODIES_FOR_SEARCHING_LIGHTEST = "There are no bodies for searching lightest body\n\n";

//constructor
BodyStreamHandler::BodyStreamHandler()
{
}

//helper methods
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


bool BodyStreamHandler::PushConeInVector(stringstream& parameters)
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
		if (isPositiveNumbers({ density, width, depth, height }))
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


bool BodyStreamHandler::SwitchBodyToPushInVector(Bodies& nameBody, stringstream& paramsBody)
{
	switch (nameBody)
	{
	case Bodies::CYLINDER:
		if (!PushCylinderInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
			return false;
		}
		break;

	case Bodies::CONE:
		if (!PushConeInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
			return false;
		}
		break;

	case Bodies::PARALLELEPIPED:
		if (!PushParallelepipedInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
			return false;
		}
		break;

	case Bodies::SPHERE:
		if (!PushSphereInVector(paramsBody))
		{
			cout << INCORRECT_VALUES_PARAMETERS;
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}


bool BodyStreamHandler::PushBodyInVector(stringstream& paramsBody, Bodies& nameBody)
{
	if (nameBody == Bodies::NONE)
	{
		return false;
	}
	if (!SwitchBodyToPushInVector(nameBody, paramsBody))
	{
		return false;
	}
	return true;
}



////basic methods
void BodyStreamHandler::ReadBodies(istream& cin)
{
	string userInput;
	while (getline(cin, userInput))
	{
		stringstream streamUserInput(userInput);
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


void BodyStreamHandler::PrintBodiesInfo(ostream& output) const
{
	for (auto const& pointerBody : m_bodies)
	{
		output << pointerBody->ToString() << endl;
	}
}


void BodyStreamHandler::PrintMaxMassBody(ostream& output) const
{
	if (m_bodies.size() == 0)
	{
		output << NO_BODIES_FOR_SEARCHING_MAX_MASS;
		return;
	}
	output << BODY_WITH_MAX_MASS;
	auto const ptrMaxMassBody = max_element(m_bodies.begin(), m_bodies.end(), [](unique_ptr<CBody> const& a, unique_ptr<CBody> const& b)
		{
			return (*a).GetMass() < (*b).GetMass();
		}
	);
	output << (*ptrMaxMassBody)->ToString() << endl;
}


void BodyStreamHandler::PrintLightestBodyInWater(ostream& output) const
{
	if (m_bodies.size() == 0)
	{
		output << NO_BODIES_FOR_SEARCHING_LIGHTEST;
		return;
	}
	output << LIGHTEST_BODY_IN_WATER;
	auto const ptrLightestBodyInWater = std::min_element(m_bodies.begin(), m_bodies.end(), [](unique_ptr<CBody> const& a, unique_ptr<CBody> const& b)
		{
			return (*a).GetWeightInWater() < (*b).GetWeightInWater();
		}
	);
	output << (*ptrLightestBodyInWater)->ToString() << endl;
}