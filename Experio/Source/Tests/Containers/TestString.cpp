#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/LString.h"

TEST_SUITE("String", "Experio/Containers");

UNIT_TEST(TestStringHas, "String")
{
	ASSERT_TRUE(LString::HasAlpha("7je3"), "");
	ASSERT_TRUE(LString::HasAlpha("5THr"), "");
	ASSERT_FALSE(LString::HasAlpha("43582"), "");

	TEST_END();
}