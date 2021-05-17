#include "Car.h"
#include <iostream>

const short MIN_INDEX_GEAR_RANGE = 0;
const short MAX_INDEX_GEAR_RANGE = 1;

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

Car::Car() 
{

}

bool Car::IsTurnedOn() const
{
	if (engineCondition) 
	{
		return true;
	}
	return false;
}

int Car::GetDirection() const
{
	return direction;
}

int Car::GetSpeed() const
{
	return speed;
}

int Car::GetGear() const
{
	return gear;
}

bool Car::TurnOnEngine() 
{
	engineCondition = true;
	cout << SUCCESS_TURNED_ON;
	return true;
}

bool Car::TurnOffEngine() 
{
	if (!engineCondition) 
	{
		cout << SUCCESS_TURNED_OFF;
		return true;
	}
	if (speed == 0 && gear == 0)
	{
		engineCondition = false;
		cout << SUCCESS_TURNED_OFF;
		return true;
	}
	cout << SHUTDOWN_ERROR;
	cout << "reason: can\'t shutdown engine when speed or gear are not at 0 " << endl << endl;
	return false;
}

bool speedInGearRange(int speed, int gear, map<int, array<int, 2>> gearRanges) 
{
	return (speed >= gearRanges[gear][MIN_INDEX_GEAR_RANGE] && speed <= gearRanges[gear][MAX_INDEX_GEAR_RANGE]);
}

bool Car::SetGear(int gear)
{
	//conditions for false
	if (gearRanges.find(gear) == gearRanges.end()) 
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << "reason: this gear does not exist in the car"<< endl << endl;
		return false;
	}
	if (!engineCondition && gear != NEUTRAL_GEAR)
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << "reason: impossible to switch to a non-neutral gear when the engine is off" << endl << endl;
		return false;
	}
	if (gear == FIRST_GEAR && direction == DIRECTION_BACK) 
	{
		cout << gear << GEAR_CANNOT_SET;
		cout << "reason: impossible to switch to forward gear when driving backward" << endl << endl;
		return false;
	}
	if (gear == REVERSE_GEAR && direction != WITHOUT_DIRECTION)
	{
			cout << gear << GEAR_CANNOT_SET;
			cout << "reason: can't switch to reverse gear when not at rest" << endl << endl;
			return false;
	}

	//condition for true
	if (speedInGearRange(speed, gear, gearRanges))
	{
		this->gear = gear;
		cout << gear << GEAR_SET;
		return true;
	}
	cout << gear << GEAR_CANNOT_SET;
	cout << "reason: the gear doesn\'t support the current speed" << endl << endl;
	return false;
}

bool Car::SetSpeed(int speed)
{
	//conditions for false
	if (!engineCondition) 
	{
		cout << speed << SPEED_CANNOT_SET;
		cout << "reason: engine turned off" << endl << endl;
		return false;
	}
	if ((gear == NEUTRAL_GEAR && speed > this->speed) || speed < 0) 
	{
		cout << speed << SPEED_CANNOT_SET;
		cout << "reason: can't increase the speed in neutral gear" << endl << endl;
		return false;
	}

	//condition for true
	if (speedInGearRange(speed, gear, gearRanges))
	{
		if (speed == 0) 
		{
			this->speed = 0;
			direction = 0;
			cout << speed << SPEED_SET;
			return true;
		}
		if (this->speed == 0) 
		{
			if (gear > 0) 
			{
				direction = 1;
			}
			else
			{
				direction = -1;
			}
		}
		this->speed = speed;
		cout << speed << SPEED_SET;
		return true;
	}
	cout << speed << SPEED_CANNOT_SET;
	cout << "reason: the speed is out of the range of gear" << endl << endl;
	return false;
}