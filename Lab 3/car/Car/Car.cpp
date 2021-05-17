#include "Car.h"
#include <iostream>

const short MIN_INDEX_GEAR_RANGE = 0;
const short MAX_INDEX_GEAR_RANGE = 1;

const short REVERSE_GEAR = -1;
const short NEUTRAL_GEAR = 0;
const short FIRST_GEAR = 1;

const short DIRECTION_BACK = -1;
const short WITHOUT_DIRECTION = 0;

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
	cout << "The engine is turned on successfully!" << endl << endl;
	return true;
}

bool Car::TurnOffEngine() 
{
	if (!engineCondition) 
	{
		cout << "The engine is turned off successfully!" << endl << endl;
		return true;
	}
	if (speed == 0 && gear == 0)
	{
		engineCondition = false;
		cout << "The engine is turned off successfully!" << endl << endl;
		return true;
	}
	cout << "Engine shutdown error!" << endl;
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
		cout << gear << " gear can\'t be set" << endl;
		cout << "reason: this gear does not exist in the car" << endl << endl;
		return false;
	}
	if (!engineCondition && gear != NEUTRAL_GEAR)
	{
		cout << gear << " gear can\'t be set" << endl;
		cout << "reason: impossible to switch to a non-neutral gear when the engine is off" << endl << endl;
		return false;
	}
	if (gear == FIRST_GEAR && direction == DIRECTION_BACK) 
	{
		cout << gear << " gear can\'t be set" << endl;
		cout << "reason: impossible to switch to forward gear when driving backward" << endl << endl;
		return false;
	}
	if (gear == REVERSE_GEAR && direction != WITHOUT_DIRECTION)
	{
			cout << gear << " gear can\'t be set" << endl;
			cout << "reason: can't switch to reverse gear when not at rest" << endl << endl;
			return false;
	}

	//condition for true
	if (speedInGearRange(speed, gear, gearRanges))
	{
		this->gear = gear;
		cout << gear << " gear set" << endl << endl;
		return true;
	}
	cout << gear << " gear can\'t be set" << endl;
	cout << "reason: the gear doesn\'t support the current speed" << endl << endl;
	return false;
}

bool Car::SetSpeed(int speed)
{
	//conditions for false
	if (!engineCondition) 
	{
		cout << speed << " speed can\'t be set" << endl;
		cout << "reason: engine turned off" << endl << endl;
		return false;
	}
	if ((gear == NEUTRAL_GEAR && speed > this->speed) || speed < 0) 
	{
		cout << speed << " speed can\'t be set" << endl;
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
			cout << speed << " speed set" << endl << endl;
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
		cout << speed << " speed set" << endl << endl;
		return true;
	}
	cout << speed << " speed can\'t be set" << endl;
	cout << "reason: the speed is out of the range of gear" << endl << endl;
	return false;
}