#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Framework/BinaryParams.h"

TEST_SUITE("BinaryParams", "Experio/Framework");

UNIT_TEST(TestBinaryParamBasic, "BinaryParams")
{
	uint8_t uByte = 92;
	ASSERT_EQUAL(BinaryParseUByte(&uByte), 92, "");

	TEST_END();
}