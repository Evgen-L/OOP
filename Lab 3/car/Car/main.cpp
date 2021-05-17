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
	cout << "Engine: ";
	if (car.IsTurnedOn())
	{
		cout << "On" << endl;
	}
	else
	{
		cout << "Off" << endl;
	}
}

void PrintDirectionInfo(Car& car)
{
	cout << "Direction: ";
	switch (car.GetDirection())
	{
	case -1:
		cout << "Back" << endl;
		break;
	case 0:
		cout << "Without direction" << endl;
		break;
	case 1:
		cout << "Forward" << endl;
		break;
	default:
		break;
	}
}

void PrintSpeedInfo(Car& car)
{
	cout << "Speed: ";
	cout << car.GetSpeed() << endl;
}

void PrintGearInfo(Car& car)
{
	cout << "Gear: ";
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
				cout << "Incorrect gear parameter format";
				break;
			
			case Commands::SET_SPEED:
				int speed;
				if (stringAppeal >> speed)
				{
					car.SetSpeed(speed);
					break;
				}
				cout << "Incorrect speed parameter format";
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
