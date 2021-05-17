#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../Car/Car.h"

SCENARIO("IsTurnedOn: engineCondition = true")
{
	cout << "IsTurnedOn: engineCondition = true" << endl;
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.IsTurnedOn() == true);
	cout << "Done" << endl << endl;
}

SCENARIO("IsTurnedOn: engineCondition = false")
{
	cout << "IsTurnedOn: engineCondition = true" << endl;
	Car car;
	REQUIRE(car.IsTurnedOn() == false);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOnEngine")
{
	cout << "TurnOnEngine" << endl;
	Car car;
	REQUIRE(car.TurnOnEngine() == true);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: speed > 0 gear = 0")
{
	cout << "TurnOffEngine: speed > 0 gear = 0" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(car.TurnOffEngine() == false);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: speed = 0 gear != 0")
{
	cout << "TurnOffEngine: speed = 0 gear != 0" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(car.TurnOffEngine() == false);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: speed = 0 gear = 0")
{
	cout << "TurnOffEngine: speed = 0 gear = 0" << endl;
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.TurnOffEngine() == true);
	cout << "Done" << endl << endl;
}

SCENARIO("TurnOffEngine: engineCondition = false")
{
	cout << "TurnOffEngine: engineCondition = false" << endl;
	Car car;
	REQUIRE(car.TurnOffEngine() == true);
	cout << "Done" << endl << endl;
}

SCENARIO("GetDirection: gear = -1 speed = 0")
{
	cout << "GetDirection: gear = -1 speed = 0" << endl;
	Car car;
	car.SetGear(-1);
	REQUIRE(car.GetDirection() == 0);
	cout << "Done" << endl << endl;
}

SCENARIO("GetDirection: gear = -1 speed = 11")
{
	cout << "GetDirection: gear = -1 speed = 11" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(11);
	REQUIRE(car.GetDirection() == -1);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: engineCondition = false")
{
	cout << "SetSpeed: engineCondition = false" << endl;
	Car car;
	REQUIRE(car.SetGear(-1) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: engineCondition = true and gear = 0")
{
	cout << "SetSpeed: engineCondition = true and gear = 0" << endl;
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetSpeed(10) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: new speed greater than current speed in gear = 0")
{
	cout << "SetSpeed: new speed greater than current speed in gear = 0" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(car.SetSpeed(11) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: speed not in range of gear")
{
	cout << "SetSpeed: speed not in range of gear" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(car.SetSpeed(500) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetSpeed: speed in range of gear")
{
	cout << "SetSpeed: speed in range of gear" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(car.SetSpeed(10) == true);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed in range of new gear")
{
	cout << "SetGear: speed in range of new gear" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	REQUIRE(car.SetGear(2) == true);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed not in range of new gear")
{
	cout << "SetGear: speed not in range of new gear" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	REQUIRE(car.SetGear(2) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed != 0 and direction = -1 when new gear > 0")
{
	cout << "SetGear: speed != 0 and direction = -1 when new gear > 0" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(car.SetGear(1) == false);
	cout << "Done" << endl << endl;
}

SCENARIO("SetGear: speed != 0 and direction = -1 when current gear = 0 and new gear = -1")
{
	cout << "SetGear: speed != 0 and direction = -1 when current gear = 0 and new gear = -1" << endl;
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(car.SetGear(-1) == false);
	cout << "Done" << endl << endl;
}