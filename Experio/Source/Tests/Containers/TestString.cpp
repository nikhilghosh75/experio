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

UNIT_TEST(TestStringConversions, "String")
{
	ASSERT_EQUAL(LString::FloatToString(4.304, 2), "4.30", "Float to String Failed");
	ASSERT_EQUAL(LString::FloatToString(0.5, 4), "0.5000", "Float to String Failed");
	ASSERT_EQUAL(LString::FloatToString(-14.245, 3), "-14.245", "Float to String Failed");

	ASSERT_ALMOST_EQUAL(LString::StringToFloat("14.954"), 14.954);
	ASSERT_EQUAL(LString::StringToInt("45"), 45, "String to Int Failed");
	ASSERT_EQUAL(LString::StringToUInt("990"), 990, "String to UInt Failed");

	TEST_END();
}

UNIT_TEST(TestStringTrim, "String")
{
	ASSERT_EQUAL(LString::Trim(" Experio "), "Experio", "");
	ASSERT_EQUAL(LString::TrimLeft(" Experio "), "Experio ", "");
	ASSERT_EQUAL(LString::TrimRight(" Experio "), " Experio", "");

	ASSERT_EQUAL("Experio Editor    ", "Experio Editor", "");
	
	TEST_END();
}

UNIT_TEST(TestStringDigit, "String")
{
	ASSERT_EQUAL(LString::DigitToChar('0'), 0, "");
	ASSERT_EQUAL(LString::DigitToChar('7'), 7, "");

	TEST_END();
}

UNIT_TEST(TestStringNumCommas, "String")
{
	ASSERT_EQUAL(LString::NumberWithCommas(204), "204", "");
	ASSERT_EQUAL(LString::NumberWithCommas(12468), "12,468", "");

	TEST_END();
}