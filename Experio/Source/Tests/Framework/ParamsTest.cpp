#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Framework/Params.h"

TEST_SUITE("Params", "Experio/Framework");

UNIT_TEST(TestParamsVector2, "Params")
{
	std::string str1 = " {1.25 0.125} ";
	ASSERT_ALMOST_EQUAL(ParseVector2(str1).x, 1.25);
	ASSERT_ALMOST_EQUAL(ParseVector2(str1).y, 0.125);

	std::string str2 = " {2 5} ";
	ASSERT_ALMOST_EQUAL(ParseVector2(str2).x, 2);
	ASSERT_ALMOST_EQUAL(ParseVector2(str2).y, 5);

	TEST_END();
}