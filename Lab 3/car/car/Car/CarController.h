#pragma once
#include "Car.h"
#include <sstream>
using namespace std;

enum class Commands
{
	INFO,
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED
};

class CarController
{
public:
	CarController();
	void ControllCar(Car& car);
	bool GetCommand(stringstream& stringAppeal, Commands& command);
	void PrintEngineInfo(Car& car) const;
	void PrintDirectionInfo(Car& car) const;
	void PrintSpeedInfo(Car& car) const;
	void PrintGearInfo(Car& car) const;
	void getCarInfo(Car& car) const;
	bool TurnOnEngine(Car& car);
	bool TurnOffEngine(Car& car);
	bool SetGear(Car& car, int gear);
	bool SetSpeed(Car& car, int speed);
};

