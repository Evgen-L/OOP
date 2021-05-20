#pragma once
#include <map>
#include <array>

using namespace std;

class Car
{
public:
	//construct
	Car();

	//features
	bool IsTurnedOn() const;
	int GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	//actions
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool engineCondition = false;
	int speed = 0;
	int gear = 0;
	int direction = 0;
	map<int, array<int, 2>> gearRanges = 
	{ 
		{ -1, { 0, 20 } },
		{ 0, { 0, INT_MAX } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } } 
	};
};

