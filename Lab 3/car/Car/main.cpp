#include "Car.h"
#include <iostream>
#include <sstream>
#include <string>
#include <sstream>

enum class Commands
{
	INFO,
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED
};

const map<string, Commands> commands_storage = {
	{"Info", Commands::INFO},
	{ "EngineOn", Commands::ENGINE_ON },
	{ "EngineOff", Commands::ENGINE_OFF },
	{ "SetGear", Commands::SET_GEAR },
	{ "SetSpeed", Commands::SET_SPEED },
};
const string ENGINE = "Engine: ";
const string DIRECTION = "Direction: ";
const string SPEED = "Speed: ";
const string GEAR = "GEAR: ";
const string INCORRECT_GEAR_FORMAT = "Incorrect gear parameter format\n\n";
const string INCORRECT_SPEED_FORMAT = "Incorrect speed parameter format\n\n";
const string ON = "On\n";
const string OFF = "Off\n";
const string BACK = "Back\n";
const string WITHOUT_DIRECTION = "Without direction\n";
const string FORWARD = "Forward\n";
using namespace std;

bool GetCommand(stringstream& stringAppeal, Commands& command)
{
	string stringCommand;
	stringAppeal >> stringCommand;
	if (commands_storage.find(stringCommand) != commands_storage.end()) 
	{
		command = commands_storage.at(stringCommand);
		return true;
	}
	return false;
}

void PrintEngineInfo(Car& car) 
{
	cout << ENGINE;
	if (car.IsTurnedOn())
	{
		cout << ON;
	}
	else
	{
		cout << OFF;
	}
}

void PrintDirectionInfo(Car& car)
{
	cout << DIRECTION;
	switch (car.GetDirection())
	{
	case -1:
		cout << BACK;
		break;
	case 0:
		cout << WITHOUT_DIRECTION;
		break;
	case 1:
		cout << FORWARD;
		break;
	default:
		break;
	}
}

void PrintSpeedInfo(Car& car)
{
	cout << SPEED;
	cout << car.GetSpeed() << endl;
}

void PrintGearInfo(Car& car)
{
	cout << GEAR;
	cout << car.GetGear() << endl;
}

void getCarInfo(Car& car) 
{
	PrintEngineInfo(car);
	PrintDirectionInfo(car);
	PrintSpeedInfo(car);
	PrintGearInfo(car);
}

void ControllCar(Car& car) 
{
	string userAppeal;
	while (getline(cin, userAppeal))
	{
		stringstream stringAppeal(userAppeal);
		Commands command;
		if (GetCommand(stringAppeal, command))
		{
			switch (command)
			{
			
			case Commands::INFO:
				getCarInfo(car);
				break;
			
			case Commands::ENGINE_ON:
				car.TurnOnEngine();
				break;
			
			case Commands::ENGINE_OFF:
				car.TurnOffEngine();
				break;

			case Commands::SET_GEAR:
				int gear;
				if (stringAppeal >> gear) 
				{
					car.SetGear(gear);
					break;
				}
				cout << INCORRECT_GEAR_FORMAT;
				break;
			
			case Commands::SET_SPEED:
				int speed;
				if (stringAppeal >> speed)
				{
					car.SetSpeed(speed);
					break;
				}
				cout << INCORRECT_SPEED_FORMAT;
				break;
			default:
				break;
			}
		}
	}
}

int main()
{
	Car car;
	ControllCar(car);
	return 0;
}
