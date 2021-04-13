#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Framework/BinaryParams.h"

TEST_SUITE("BinaryParams", "Experio/Framework");

UNIT_TEST(TestBinaryParamBasic, "BinaryParams")
{
	int8_t byte = 31;
	ASSERT_EQUAL(BinaryParseByte(&byte), 31, "");

	uint8_t uByte = 92;
	ASSERT_EQUAL(BinaryParseUByte(&uByte), 92, "");

	int16_t shortInt = 450;
	ASSERT_EQUAL(BinaryParseShort(&shortInt), 450, "");

	uint16_t uShortInt = 1213;
	ASSERT_EQUAL(BinaryParseUShort(&uShortInt), 1213, "");

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

UNIT_TEST(TestBinaryParamVector4, "BinaryParams")
{
	FVector4 v(10, 11, 12, 13);

	ASSERT_ALMOST_EQUAL(BinaryParseVector4(&v).w, 10);
	ASSERT_ALMOST_EQUAL(BinaryParseVector4(&v).x, 11);
	ASSERT_ALMOST_EQUAL(BinaryParseVector4(&v).y, 12);
	ASSERT_ALMOST_EQUAL(BinaryParseVector4(&v).z, 13);

	TEST_END();
}