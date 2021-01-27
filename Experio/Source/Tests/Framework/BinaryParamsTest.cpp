#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Framework/BinaryParams.h"

TEST_SUITE("BinaryParams", "Experio/Framework");

UNIT_TEST(TestBinaryParamBasic, "BinaryParams")
{
	int8_t byte = 31;
	ASSERT_EQUAL(BinaryParseByte(&byte), 31, "");

	uint8_t uByte = 92;
	ASSERT_EQUAL(BinaryParseUByte(&uByte), 92, "");

	TEST_END();
}

UNIT_TEST(TestBinaryParamVector2, "BinaryParams")
{
	FVector2 v(4, 5);
	ASSERT_ALMOST_EQUAL(BinaryParseVector2(&v).x, 4);
	ASSERT_ALMOST_EQUAL(BinaryParseVector2(&v).y, 5);

	TEST_END();
}

UNIT_TEST(TestBinaryParamVector3, "BinaryParams")
{
	FVector3 v(7, 8, 9);
	ASSERT_ALMOST_EQUAL(BinaryParseVector3(&v).x, 7);
	ASSERT_ALMOST_EQUAL(BinaryParseVector3(&v).y, 8);
	ASSERT_ALMOST_EQUAL(BinaryParseVector3(&v).z, 9);

	TEST_END();
}