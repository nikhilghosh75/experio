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

UNIT_TEST(TestStringFind, "String")
{
	ASSERT_EQUAL(LString::FindFirstOfChar("Wolvey", 'v'), 3, "");
	ASSERT_EQUAL(LString::FindFirstOfChars("Wolvey", { 'e', 'l' }), 2, "");

	ASSERT_EQUAL(LString::FindAllOfChar("Nikhil Ghosh", 'i').size(), 2, "");
	ASSERT_EQUAL(LString::FindAllOfChar("Nikhil Ghosh", 'i')[0], 1, "");
	ASSERT_EQUAL(LString::FindAllOfChar("Nikhil Ghosh", 'i')[1], 4, "");

	TEST_END();
}

UNIT_TEST(TestStringFloatVector, "String")
{
	std::string str = "1.1 2.2 3.3 14.5 6.7 9.4";
	std::vector<float> floats = LString::StringToFloatVector(str);

	ASSERT_EQUAL(floats.size(), 6, "");
	ASSERT_ALMOST_EQUAL(floats[0], 1.1f);
	ASSERT_ALMOST_EQUAL(floats[1], 2.2f);
	ASSERT_ALMOST_EQUAL(floats[2], 3.3f);
	ASSERT_ALMOST_EQUAL(floats[3], 14.5f);
	ASSERT_ALMOST_EQUAL(floats[4], 6.7f);
	ASSERT_ALMOST_EQUAL(floats[5], 9.4f);

	TEST_END();
}