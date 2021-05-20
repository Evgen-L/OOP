#include "Car.h"

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
	return true;
}

bool Car::TurnOffEngine() 
{
	if (!engineCondition) 
	{
		return true;
	}
	if (speed == 0 && gear == 0)
	{
		engineCondition = false;
		return true;
	}
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
		return false;
	}
	if (!engineCondition && gear != NEUTRAL_GEAR)
	{
		return false;
	}
	if (gear == FIRST_GEAR && direction == DIRECTION_BACK) 
	{
		return false;
	}
	if (gear == REVERSE_GEAR && direction != WITHOUT_DIRECTION)
	{
			return false;
	}

	//condition for true
	if (speedInGearRange(speed, gear, gearRanges))
	{
		this->gear = gear;
		return true;
	}

	return false;
}

bool Car::SetSpeed(int speed)
{
	//conditions for false
	if (!engineCondition) 
	{
		return false;
	}
	if ((gear == NEUTRAL_GEAR && speed > this->speed) || speed < 0) 
	{
		return false;
	}

	//condition for true
	if (speedInGearRange(speed, gear, gearRanges))
	{
		if (speed == 0) 
		{
			this->speed = 0;
			direction = 0;
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
		return true;
	}
	return false;
}