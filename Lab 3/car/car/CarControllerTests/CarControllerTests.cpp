#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../Car/CarController.h"

SCENARIO("GetCommand: command =  Info")
{
	cout << "GetCommand: command =  Info" << endl;
	CarController controller;
	stringstream stringCommand("Info");
	Commands command;
	REQUIRE(controller.GetCommand(stringCommand, command) == true);
	REQUIRE(command == Commands::INFO);
	cout << "Done" << endl << endl;
}

SCENARIO("GetCommand: command =  SetGear1 (without space)")
{
	cout << "GetCommand: command = SetGear1(without space)" << endl;
	CarController controller;
	stringstream stringCommand("SetGear1");
	Commands command;
	REQUIRE(controller.GetCommand(stringCommand, command) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("GetCommand: command =  SetGear 1 (with space)")
{
	cout << "GetCommand: command = SetGear 1(with space)" << endl;
	CarController controller;
	stringstream stringCommand("SetGear 1");
	Commands command;
	REQUIRE(controller.GetCommand(stringCommand, command) == true);
	REQUIRE(command == Commands::SET_GEAR);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOnEngine")
{
	cout << "TurnOnEngine" << endl;
	CarController controller;
	Car car;
	REQUIRE(controller.TurnOnEngine(car) == true);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: speed > 0 gear = 0")
{
	cout << "TurnOffEngine: speed > 0 gear = 0" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(controller.TurnOffEngine(car) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: speed = 0 gear != 0")
{
	cout << "TurnOffEngine: speed = 0 gear != 0" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(controller.TurnOffEngine(car) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: speed = 0 gear = 0")
{
	cout << "TurnOffEngine: speed = 0 gear = 0" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	REQUIRE(controller.TurnOffEngine(car) == true);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: engineCondition = false")
{
	cout << "TurnOffEngine: engineCondition = false" << endl;
	CarController controller;
	Car car;
	REQUIRE(controller.TurnOffEngine(car) == true);
	cout << "Done" << endl << endl;
}



SCENARIO("SetSpeed: engineCondition = false")
{
	cout << "SetSpeed: engineCondition = false" << endl;
	CarController controller;
	Car car;
	REQUIRE(controller.SetGear(car, -1) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: engineCondition = true and gear = 0")
{
	cout << "SetSpeed: engineCondition = true and gear = 0" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	REQUIRE(controller.SetSpeed(car, 10) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: new speed greater than current speed in gear = 0")
{
	cout << "SetSpeed: new speed greater than current speed in gear = 0" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(controller.SetSpeed(car, 11) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: speed not in range of gear")
{
	cout << "SetSpeed: speed not in range of gear" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(controller.SetSpeed(car, 500) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: speed in range of gear")
{
	cout << "SetSpeed: speed in range of gear" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(controller.SetSpeed(car, 10) == true);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed in range of new gear")
{
	cout << "SetGear: speed in range of new gear" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	REQUIRE(controller.SetGear(car, 2) == true);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed not in range of new gear")
{
	cout << "SetGear: speed not in range of new gear" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	REQUIRE(controller.SetGear(car, 2) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed != 0 and direction = -1 when new gear > 0")
{
	cout << "SetGear: speed != 0 and direction = -1 when new gear > 0" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(controller.SetGear(car, 1) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed != 0 and direction = -1 when current gear = 0 and new gear = -1")
{
	cout << "SetGear: speed != 0 and direction = -1 when current gear = 0 and new gear = -1" << endl;
	CarController controller;
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(controller.SetGear(car, -1) == false);
	cout << "Done" << endl << endl;
}

