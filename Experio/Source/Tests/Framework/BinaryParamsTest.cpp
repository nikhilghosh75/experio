#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Framework/BinaryParams.h"

TEST_SUITE("BinaryParam", "Experio/Framework");

UNIT_TEST(TestBinaryParamBasic, "BinaryParam")
{
	int8_t byte = 31;
	ASSERT_EQUAL(BinaryParseByte(&byte), 31, "");

	uint8_t uByte = 92;
	ASSERT_EQUAL(BinaryParseUByte(&uByte), 92, "");

	TEST_END();
}

UNIT_TEST(TestBinaryParamVector2, "BinaryParam")
{
	FVector2 v(4, 5);
	ASSERT_ALMOST_EQUAL(BinaryParseVector2(&v).x, 4);
	ASSERT_ALMOST_EQUAL(BinaryParseVector2(&v).y, 5);

	TEST_END();
}