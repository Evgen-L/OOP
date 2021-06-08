#include <iostream>
#include "../BodyStreamHandler/BodyStreamHandler.h"

int main()
{
	BodyStreamHandler handler;
	handler.ReadBodies(cin);
	handler.PrintBodiesInfo(cout);
	handler.PrintMaxMassBody(cout);
	handler.PrintLightestBodyInWater(cout);
}

