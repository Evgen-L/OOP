#include <iostream>
#include "../BodyStreamHandler/BodyStreamHandler.h"

int main()
{
	BodyStreamHandler handler;
	handler.ReadBodies(cin);
	handler.PrintBodiesInfo();
	handler.PrintMaxMassBody();
	handler.PrintLightestBodyInWater();
}

