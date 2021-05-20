#include "CarController.h"
#include <iostream>
#include <sstream>
#include <string>

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
const short NO_DIRECTION = 0;

const string ENGINE = "Engine: ";
const string DIRECTION = "Direction: ";
const string SPEED = "Speed: ";
const string GEAR = "GEAR: ";
const string ON = "On\n";
const string OFF = "Off\n";
const string BACK = "Back\n";
const string WITHOUT_DIRECTION = "Without direction\n";
const string FORWARD = "Forward\n";
const string INCORRECT_GEAR_FORMAT = "Incorrect gear parameter format\n\n";
const string INCORRECT_SPEED_FORMAT = "Incorrect speed parameter format\n\n";

const string SUCCESS_TURNED_ON = "The engine is turned on successfully!\n\n";
const string SUCCESS_TURNED_OFF = "The engine is turned off successfully!\n\n";
const string SHUTDOWN_ERROR = "shutdown error!\n\n";
const string GEAR_CANNOT_SET = " gear can\'t be set\n";
const string GEAR_SET = " gear set\n\n";
const string SPEED_CANNOT_SET = " speed can\'t be set\n";
const string SPEED_SET = " speed set\n\n";

const string REASON_CANNOT_SHUTDOWN_ENGINE_WHEN_SPEED_GEAR_NULL = "reason: can\'t shutdown engine when speed or gear are not at 0\n\n ";
const string REASON_GEAR_NOT_EXIST = "reason: this gear does not exist in the car\n\n";
const string REASON_CANNOT_SET_NON_NEUTRAL_GEAR_WHEN_ENGINE_OFF = "reason: impossible to switch to a non-neutral gear when the engine is off\n\n";
const string REASON_CANNOT_SET_FORWARD_GEAR_WHEN_DRIVING_BACKWARD = "reason: impossible to switch to forward gear when driving backward\n\n";
const string REASON_CANNOT_SET_REVERSE_GEAR_WHEN_NOT_REST = "reason: can't switch to reverse gear when not at rest\n\n";
const string REASON_GEAR_NOT_SUPPORT_SPEED = "reason: the gear doesn\'t support the current speed\n\n";
const string REASON_ENGINE_OFF = "reason: engine turned off\n\n";
const string REASON_CANNOT_INCREASE_SPEED_IN_NEUTRAL_GEAR = "reason: can't increase the speed in neutral gear\n\n";
const string REASON_SPEED_OUT_OF_RANGE_OF_GEAR = "reason: the speed is out of the range of gear\n\n";
const string COMMAND_NOT_EXIST= "This command does not exist\n\n";

using namespace std;



bool CarController::GetCommand(stringstream& stringAppeal, Commands& command) 
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


void CarController::PrintEngineInfo(Car& car) const
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

void CarController::PrintDirectionInfo(Car& car) const
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

void CarController::PrintSpeedInfo(Car& car) const
{
	cout << SPEED;
	cout << car.GetSpeed() << endl;
}

void CarController::PrintGearInfo(Car& car) const
{
	cout << GEAR;
	cout << car.GetGear() << endl;
}

void CarController::getCarInfo(Car& car) const
{
	CarController::PrintEngineInfo(car);
	CarController::PrintDirectionInfo(car);
	CarController::PrintSpeedInfo(car);
	CarController::PrintGearInfo(car);
	cout << endl;
}

bool CarController::TurnOnEngine(Car& car) 
{
	car.TurnOnEngine();
	cout << SUCCESS_TURNED_ON;
	return true;
}

bool CarController::TurnOffEngine(Car& car)
{
	//conditions for true
	if (!car.IsTurnedOn())
	{
		cout << SUCCESS_TURNED_OFF;
		return true;
	}
	if (car.GetSpeed() == 0 && car.GetGear() == 0)
	{
		car.TurnOffEngine();
		cout << SUCCESS_TURNED_OFF;
		return true;
	}
	//else false
	cout << SHUTDOWN_ERROR;
	cout << REASON_CANNOT_SHUTDOWN_ENGINE_WHEN_SPEED_GEAR_NULL;
	return false;
}

bool CarController::SetGear(Car& car, int gear)
{
	//conditions for false
	if (gear < MIN_GEAR || gear > MAX_GEAR)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << REASON_GEAR_NOT_EXIST;
		return false;
	}
	if (!car.IsTurnedOn() && gear != NEUTRAL_GEAR)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << REASON_CANNOT_SET_NON_NEUTRAL_GEAR_WHEN_ENGINE_OFF;
		return false;
	}
	if (gear == FIRST_GEAR && car.GetDirection() == DIRECTION_BACK)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << REASON_CANNOT_SET_FORWARD_GEAR_WHEN_DRIVING_BACKWARD;
		return false;
	}
	if (gear == REVERSE_GEAR && car.GetDirection() != NO_DIRECTION)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << REASON_CANNOT_SET_REVERSE_GEAR_WHEN_NOT_REST;
		return false;
	}

	//condition for true
	if (car.SetGear(gear))
	{
		cout << gear << GEAR_SET;
		return true;
	}
	cout << gear << GEAR_CANNOT_SET;
	cout << REASON_GEAR_NOT_SUPPORT_SPEED;
	return false;
}

bool CarController::SetSpeed(Car& car, int speed)
{

	//conditions for false
	if (!car.IsTurnedOn())
	{
		cout << speed << SPEED_CANNOT_SET;
		cout << REASON_ENGINE_OFF;
		return false;
	}
	if ((car.GetGear() == NEUTRAL_GEAR && speed > car.GetSpeed()) || speed < 0)
	{
		cout << speed << SPEED_CANNOT_SET;
		cout << REASON_CANNOT_INCREASE_SPEED_IN_NEUTRAL_GEAR;
		return false;
	}

	//condition for true
	if (car.SetSpeed(speed))
	{
		cout << speed << SPEED_SET;
		return true;
	}
	cout << speed << SPEED_CANNOT_SET;
	cout << REASON_SPEED_OUT_OF_RANGE_OF_GEAR;
	return false;
}

CarController::CarController() {};

void CarController::ControllCar(Car& car) 
{
	string userAppeal;
	while (getline(cin, userAppeal))
	{
		stringstream stringAppeal(userAppeal);
		Commands command;
		if (CarController::GetCommand(stringAppeal, command))
		{
			switch (command)
			{

			case Commands::INFO:
				CarController::getCarInfo(car);
				break;

			case Commands::ENGINE_ON:
				CarController::TurnOnEngine(car);
				break;

			case Commands::ENGINE_OFF:
				CarController::TurnOffEngine(car);
				break;

			case Commands::SET_GEAR:
				int gear;
				if (stringAppeal >> gear)
				{
					CarController::SetGear(car, gear);
					break;
				}
				cout << INCORRECT_GEAR_FORMAT;
				break;

			case Commands::SET_SPEED:
				int speed;
				if (stringAppeal >> speed)
				{
					CarController::SetSpeed(car, speed);
					break;
				}
				cout << INCORRECT_SPEED_FORMAT;
				break;
			default:
				break;
			}
		}
		else 
		{
			cout << COMMAND_NOT_EXIST;
		}
	}
}