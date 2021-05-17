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

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

const short REVERSE_GEAR = -1;
const short NEUTRAL_GEAR = 0;
const short FIRST_GEAR = 1;

const short DIRECTION_BACK = -1;
const short WITHOUT_DIRECTION = 0;


const string SUCCESS_TURNED_ON = "The engine is turned on successfully!\n\n";
const string SUCCESS_TURNED_OFF = "The engine is turned off successfully!\n\n";
const string SHUTDOWN_ERROR = "shutdown error!\n\n";
const string GEAR_CANNOT_SET = " gear can\'t be set\n";
const string GEAR_SET = " gear set\n\n";
const string SPEED_CANNOT_SET = "speed can\'t be set\n";
const string SPEED_SET = " speed set\n\n";

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

void TurnOnEngine(Car& car) 
{
	car.TurnOnEngine();
	cout << SUCCESS_TURNED_ON;
}

void TurnOffEngine(Car& car)
{
	//conditions for true
	if (!car.IsTurnedOn())
	{
		cout << SUCCESS_TURNED_OFF;
		return;
	}
	if (car.GetSpeed()== 0 && car.GetGear()== 0)
	{
		car.TurnOffEngine();
		cout << SUCCESS_TURNED_OFF;
		return;
	}
	//else false
	cout << SHUTDOWN_ERROR;
	cout << "reason: can\'t shutdown engine when speed or gear are not at 0 " << endl << endl;
}

void SetGear(Car& car, int gear)
{
	//conditions for false
	if (gear < MIN_GEAR  || gear > MAX_GEAR)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << "reason: this gear does not exist in the car" << endl << endl;
		return;
	}
	if (!car.IsTurnedOn() && gear != NEUTRAL_GEAR)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << "reason: impossible to switch to a non-neutral gear when the engine is off" << endl << endl;
		return;
	}
	if (gear == FIRST_GEAR && car.GetDirection() == DIRECTION_BACK)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << "reason: impossible to switch to forward gear when driving backward" << endl << endl;
		return;
	}
	if (gear == REVERSE_GEAR && car.GetDirection() != WITHOUT_DIRECTION)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << "reason: can't switch to reverse gear when not at rest" << endl << endl;
		return;
	}

	//condition for true
	if (car.SetGear(gear))
	{
		cout << gear << GEAR_SET;
		return;
	}
	cout << gear << GEAR_CANNOT_SET;
	cout << "reason: the gear doesn\'t support the current speed" << endl << endl;
}

void SetSpeed(Car& car, int speed)
{

	//conditions for false
	if (!car.IsTurnedOn())
	{
		cout << speed << SPEED_CANNOT_SET;
		cout << "reason: engine turned off" << endl << endl;
		return;
	}
	if ((car.GetGear() == NEUTRAL_GEAR && speed > car.GetSpeed()) || speed < 0)
	{
		cout << speed << SPEED_CANNOT_SET;
		cout << "reason: can't increase the speed in neutral gear" << endl << endl;
		return;
	}

	//condition for true
	if (car.SetSpeed(speed))
	{
		cout << speed << SPEED_SET;	
		return;
	}
	cout << speed << SPEED_CANNOT_SET;
	cout << "reason: the speed is out of the range of gear" << endl << endl;
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
				TurnOnEngine(car);
				break;
			
			case Commands::ENGINE_OFF:
				TurnOffEngine(car);
				break;

			case Commands::SET_GEAR:
				int gear;
				if (stringAppeal >> gear) 
				{
					SetGear(car, gear);
					break;
				}
				cout << "Incorrect gear parameter format";
				break;
			
			case Commands::SET_SPEED:
				int speed;
				if (stringAppeal >> speed)
				{
					SetSpeed(car, speed);
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

