#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <map>
#include "../Car/Car.h"

enum class Commands
{
	INFO,
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED
};


bool GetCommand(stringstream& stringAppeal, Commands& command);
void PrintEngineInfo(Car& car);
void PrintDirectionInfo(Car& car);
void PrintSpeedInfo(Car& car);
void PrintGearInfo(Car& car);
void getCarInfo(Car& car);
bool TurnOnEngine(Car& car);
bool TurnOffEngine(Car& car);
bool SetGear(Car& car, int gear);
bool SetSpeed(Car& car, int speed);