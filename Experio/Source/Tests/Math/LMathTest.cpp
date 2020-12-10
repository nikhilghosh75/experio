#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Math/LMath.h"

TEST_SUITE("LMath", "Experio/Math");

UNIT_TEST(TestMathAcos, "LMath")
{
	ASSERT_ALMOST_EQUAL(LMath::Acos(1), 0);
	ASSERT_ALMOST_EQUAL(LMath::Acos(0.3f), 1.2661f);
	ASSERT_ALMOST_EQUAL(LMath::Acos(0.65f), 0.8632f);
	ASSERT_ALMOST_EQUAL(LMath::Acos(0.97f), 0.2455f);
	ASSERT_ALMOST_EQUAL(LMath::Acos(0), 1.5707f);

	TEST_END();
}

UNIT_TEST(TestMathAsin, "LMath")
{
	ASSERT_ALMOST_EQUAL(LMath::Asin(0), 1);
	ASSERT_ALMOST_EQUAL(LMath::Asin(0.45f), 0.4668f);
	ASSERT_ALMOST_EQUAL(LMath::Asin(0.71f), 0.7895f);
	ASSERT_ALMOST_EQUAL(LMath::Asin(0.97f), 1.3252f);
	ASSERT_ALMOST_EQUAL(LMath::Asin(1), 1.5707f);

	TEST_END();
}

UNIT_TEST(TestMathAbs, "LMath")
{
	ASSERT_ALMOST_EQUAL(LMath::Abs(1), 1);
	ASSERT_ALMOST_EQUAL(LMath::Abs(-1), 1);

	TEST_END();
}

UNIT_TEST(TestMathAtan, "LMath")
{
	ASSERT_ALMOST_EQUAL(LMath::Atan(0), 0);
	ASSERT_ALMOST_EQUAL(LMath::Atan(0.25f), 0.2450f);
	ASSERT_ALMOST_EQUAL(LMath::Asin(0.52f), 0.4795f);
	ASSERT_ALMOST_EQUAL(LMath::Asin(1.11f), 0.8375f);

	ASSERT_ALMOST_EQUAL(LMath::Atan2(0, 1), HALFPI);
	ASSERT_ALMOST_EQUAL(LMath::Atan2(1, 0), -HALFPI);
	ASSERT_ALMOST_EQUAL(LMath::Atan2(1, 1), 0.7854f);
	ASSERT_ALMOST_EQUAL(LMath::Atan2(-2, 1), 2.6780f);
	ASSERT_ALMOST_EQUAL(LMath::Atan2(7, -3), -0.4049f);
	ASSERT_ALMOST_EQUAL(LMath::Atan2(-8, -3), -2.7828f);

	TEST_END();
}

UNIT_TEST(TestMathBetween, "LMath")
{
	ASSERT_TRUE(LMath::Between(0.f, 1.f, 0.5f), "");
	ASSERT_FALSE(LMath::Between(-1.f, 2.f, 3.f), "");

	TEST_END();
}

UNIT_TEST(TestMathBinomial, "LMath")
{
	ASSERT_ALMOST_EQUAL(LMath::BinomialCoefficent(10, 3), 120);
	ASSERT_ALMOST_EQUAL(LMath::BinomialCoefficent(10, 7), 120);
	ASSERT_ALMOST_EQUAL(LMath::BinomialCoefficent(10, 0), 1);
	ASSERT_ALMOST_EQUAL(LMath::BinomialCoefficent(13, 13), 1);

	TEST_END();
}

UNIT_TEST(TestMathClamp, "LMath")
{
	ASSERT_ALMOST_EQUAL(LMath::Clamp(10, 0, 5), 5);
	ASSERT_ALMOST_EQUAL(LMath::Clamp(10, 15, 20), 15);
	
	TEST_END();
}

FUnitTestingOutcome RunLMathTests()
{
	return suite.RunTests();
}
