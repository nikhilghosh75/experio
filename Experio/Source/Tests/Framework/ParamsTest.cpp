#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Framework/Params.h"

TEST_SUITE("Params", "Experio/Framework");

UNIT_TEST(TestParamsBool, "Params")
{
	std::string trueStr = "true";
	std::string falseStr = "false";

	ASSERT_TRUE(ParseBool(trueStr), "");
	ASSERT_FALSE(ParseBool(falseStr), "");

	TEST_END();
}

UNIT_TEST(TestParamsByte, "Params")
{
	std::string byteStr = "48";
	std::string negativeByteStr = "-20";

	ASSERT_EQUAL(ParseByte(byteStr), 48, "");
	ASSERT_EQUAL(ParseByte(negativeByteStr), -20, "");

	std::string uByteStr = "212";
	ASSERT_EQUAL(ParseUByte(uByteStr), 212, "");

	TEST_END();
}

UNIT_TEST(TestParamsShort, "Params")
{
	std::string shortStr = "450";
	std::string negativeShortStr = "-342";

	ASSERT_EQUAL(ParseShort(shortStr), 450, "");
	ASSERT_EQUAL(ParseShort(negativeShortStr), -342, "");
	
	std::string uShortStr = "48754";
	ASSERT_EQUAL(ParseUShort(uShortStr), 48754, "");

	TEST_END();
}

UNIT_TEST(TestParamsInt, "Params")
{
	std::string intStr = "96024";
	std::string negativeIntStr = "-103485";
	std::string uintStr = "14902149";

	ASSERT_EQUAL(ParseInt(intStr), 96024, "");
	ASSERT_EQUAL(ParseInt(negativeIntStr), -103485, "");
	ASSERT_EQUAL(ParseUInt(uintStr), 14902149, "");

	TEST_END();
}

UNIT_TEST(TestParamsFloat, "Params")
{
	std::string floatStr = "4.596";

	ASSERT_ALMOST_EQUAL(ParseFloat(floatStr), 4.596, "");

	TEST_END();
}

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

UNIT_TEST(TestParamsVector3, "Params")
{
	std::string str1 = "{3.00 0.45 4.60}";

	ASSERT_ALMOST_EQUAL(ParseVector3(str1).x, 3);
	ASSERT_ALMOST_EQUAL(ParseVector3(str1).y, 0.45);
	ASSERT_ALMOST_EQUAL(ParseVector3(str1).z, 4.60);

	TEST_END();
}

UNIT_TEST(TestParamsVector4, "Params")
{
	std::string str1 = "{5.714 3.00 0.45 4.60}";

	ASSERT_ALMOST_EQUAL(ParseVector4(str1).w, 5.714);
	ASSERT_ALMOST_EQUAL(ParseVector4(str1).x, 3);
	ASSERT_ALMOST_EQUAL(ParseVector4(str1).y, 0.45);
	ASSERT_ALMOST_EQUAL(ParseVector4(str1).z, 4.60);

	TEST_END();
}

UNIT_TEST(TestParamsQuaternion, "Params")
{
	std::string str1 = "{5.714 3.00 0.45 4.60}";

	ASSERT_ALMOST_EQUAL(ParseQuaternion(str1).x, 5.714);
	ASSERT_ALMOST_EQUAL(ParseQuaternion(str1).y, 3);
	ASSERT_ALMOST_EQUAL(ParseQuaternion(str1).z, 0.45);
	ASSERT_ALMOST_EQUAL(ParseQuaternion(str1).w, 4.60);

	TEST_END();
}