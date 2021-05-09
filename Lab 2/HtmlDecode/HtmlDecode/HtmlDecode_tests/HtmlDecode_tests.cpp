// HtmlDecode_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../HtmlDecode/Decoder.h"

SCENARIO("empty input")
{
	cout <<"empty input" << endl;
	REQUIRE(HtmlDecode("") == "");
	REQUIRE(ReplaceStr("", "&quot;", "\"") == "");
}

SCENARIO("replace &apos;")
{
	cout << "replace &apos;" << endl;
	REQUIRE(ReplaceStr("huston we &amp; have &amp; some problems &lt;&gt; histon sdigsdvf &apos;",         "&apos;", "\'") == "huston we &amp; have &amp; some problems &lt;&gt; histon sdigsdvf \'");
}

SCENARIO("replace &gt;")
{
	cout << "replace &gt;" << endl;
	REQUIRE(ReplaceStr("huston we &amp; have &amp; some problems &lt;&gt; histon sdigsdvf &apos;",          "&gt;", ">") == "huston we &amp; have &amp; some problems &lt;> histon sdigsdvf &apos;");
}


SCENARIO("HtmlDecode")
{
	cout << "HtmlDecode" << endl;
	REQUIRE(HtmlDecode("&quot;&quot;Huston! &apos; We &lt; have problem &gt;here&amp;") == "\"\"Huston! \' We < have problem >here&");
}
