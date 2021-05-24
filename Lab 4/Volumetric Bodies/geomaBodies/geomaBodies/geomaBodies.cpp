#include <iostream>
#include "../BodyStreamHandler/BodyStreamHandler.h"

int main()
{
	BodyStreamHandler handler;
	handler.ReadBodies();
	handler.PrintBodiesInfo();
	handler.PrintMaxMassBody();
	handler.PrintLightestBodyInWater();
}

