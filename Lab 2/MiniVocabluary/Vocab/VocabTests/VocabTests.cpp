#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../../Vocab/Vocab/VocabFuncs.h"

using namespace std;

SCENARIO("Lower: with lower case")
{
	string cat = "cat";
	REQUIRE(Lower(cat) == "cat");
}

SCENARIO("Lower: with different case")
{
	string cat = "CaT";
	REQUIRE(Lower(cat) == "cat");
}

SCENARIO("Lower: with empty string")
{
	string cat = "";
	REQUIRE(Lower(cat) == "");
}
