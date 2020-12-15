#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/LString.h"

TEST_SUITE("String", "Experio/Containers");

UNIT_TEST(TestStringHas, "String")
{
	ASSERT_TRUE(LString::HasAlpha("7je3"), "");
	ASSERT_TRUE(LString::HasAlpha("5THr"), "");
	ASSERT_FALSE(LString::HasAlpha("43582"), "");

	ASSERT_TRUE(LString::HasAlphaNumeric("R32fd5."), "");
	ASSERT_FALSE(LString::HasAlphaNumeric(".;!#"), "");

	ASSERT_TRUE(LString::HasChar("45678", '4'), "");
	ASSERT_FALSE(LString::HasChar("abcde", 'f'), "");

	ASSERT_TRUE(LString::HasOneOfEachChar("abcde", { 'a', 'e', 'c' }), "");
	ASSERT_TRUE(LString::HasOneOfEachChar("abcde", { 'a', 'f' }), "");

	TEST_END();
}