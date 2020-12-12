#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Math/FVector3.h"

TEST_SUITE("Vector3", "Experio/Math");

UNIT_TEST(TestVector3Magnitude, "Vector3")
{
	FVector3 v(3, 3, 0);

	ASSERT_ALMOST_EQUAL(FVector3::Magnitude(v), 4.243f);
	ASSERT_ALMOST_EQUAL(FVector3::SqrMagnitude(v), 18);

	FVector3 zero(0, 0, 0);
	ASSERT_ALMOST_EQUAL(FVector3::Magnitude(v), 0);
	ASSERT_ALMOST_EQUAL(FVector3::SqrMagnitude(v), 0);

	TEST_END();
}

UNIT_TEST(TestVector3Normalized, "Vector3")
{
	FVector3 v(3, 6, 9);
	FVector3 normalized = FVector3::Normalized(v);

	ASSERT_FALSE(FVector3::IsNormalized(v), "");
	ASSERT_TRUE(FVector3::IsNormalized(normalized), "");

	ASSERT_ALMOST_EQUAL(FVector3::Magnitude(normalized), 1);
	ASSERT_ALMOST_EQUAL(FVector3::SqrMagnitude(normalized), 1);

	ASSERT_ALMOST_EQUAL(normalized.x, 0.26726f);
	ASSERT_ALMOST_EQUAL(normalized.y, 0.53452f);
	ASSERT_ALMOST_EQUAL(normalized.z, 0.80178f);

	TEST_END();
}

UNIT_TEST(TestVector3Zero, "Vector3")
{
	FVector3 v(3, 6, 9);
	FVector3 zero(0, 0, 0);
	FVector3 up(0, 1, 0);
	FVector3 right(1, 0, 0);
	FVector3 in(0, 0, 1);

	ASSERT_FALSE(FVector3::IsZero(v), "");
	ASSERT_TRUE(FVector3::IsZero(zero), "");
	ASSERT_FALSE(FVector3::IsZero(up), "");
	ASSERT_FALSE(FVector3::IsZero(right), "");
	ASSERT_FALSE(FVector3::IsZero(in), "");

	TEST_END();
}

UNIT_TEST(TestVector3Products, "Vector3")
{
	FVector3 v1(1, 2, 3);
	FVector3 v2(4, 5, 6);

	float dot = FVector3::Dot(v1, v2);
	FVector3 cross = FVector3::Cross(v1, v2);

	ASSERT_ALMOST_EQUAL(dot, 32);
	ASSERT_ALMOST_EQUAL(cross.x, -3);
	ASSERT_ALMOST_EQUAL(cross.y, 6);
	ASSERT_ALMOST_EQUAL(cross.z, -3);

	dot = FVector3::Dot(v2, v1);
	cross = FVector3::Cross(v2, v1);
	ASSERT_ALMOST_EQUAL(dot, 32);
	ASSERT_ALMOST_EQUAL(cross.x, -3);
	ASSERT_ALMOST_EQUAL(cross.y, 6);
	ASSERT_ALMOST_EQUAL(cross.z, -3);

	ASSERT_ALMOST_EQUAL(FVector3::Dot(v1, v1), 6);

	TEST_END();
}

UNIT_TEST(TestVector3Lerp, "Vector3")
{
	FVector3 v1(1, 1, 1);
	FVector3 v2(9, 13, 17);

	FVector3 zero = FVector3::Lerp(v1, v2, 0);
	ASSERT_ALMOST_EQUAL(zero.x, 1);
	ASSERT_ALMOST_EQUAL(zero.y, 1);
	ASSERT_ALMOST_EQUAL(zero.z, 1);

	FVector3 twentyFive = FVector3::Lerp(v1, v2, 0.25f);
	ASSERT_ALMOST_EQUAL(twentyFive.x, 3);
	ASSERT_ALMOST_EQUAL(twentyFive.y, 4);
	ASSERT_ALMOST_EQUAL(twentyFive.z, 5);

	FVector3 half = FVector3::Lerp(v1, v2, 0.5f);
	ASSERT_ALMOST_EQUAL(half.x, 5);
	ASSERT_ALMOST_EQUAL(half.y, 7);
	ASSERT_ALMOST_EQUAL(half.z, 9);

	FVector3 threeQuarter = FVector3::Lerp(v1, v2, 0.75f);
	ASSERT_ALMOST_EQUAL(threeQuarter.x, 7);
	ASSERT_ALMOST_EQUAL(threeQuarter.y, 10);
	ASSERT_ALMOST_EQUAL(threeQuarter.z, 13);

	FVector3 one = FVector3::Lerp(v1, v2, 1);
	ASSERT_ALMOST_EQUAL(one.x, 9);
	ASSERT_ALMOST_EQUAL(one.y, 13);
	ASSERT_ALMOST_EQUAL(one.z, 17);

	TEST_END();
}

UNIT_TEST(TestVector3Operations, "Vector3")
{
	FVector3 v1(2, 3, 4);
	FVector3 v2(6, 7, 8);

	FVector3 addResult = v1 + v2;
	ASSERT_ALMOST_EQUAL(addResult.x, 8);
	ASSERT_ALMOST_EQUAL(addResult.y, 10);
	ASSERT_ALMOST_EQUAL(addResult.z, 12);

	addResult += FVector3(1, 1, 1);
	ASSERT_ALMOST_EQUAL(addResult.x, 9);
	ASSERT_ALMOST_EQUAL(addResult.y, 11);
	ASSERT_ALMOST_EQUAL(addResult.z, 13);

	FVector3 subtractResult = v2 - v1;
	ASSERT_ALMOST_EQUAL(subtractResult.x, 4);
	ASSERT_ALMOST_EQUAL(subtractResult.y, 4);
	ASSERT_ALMOST_EQUAL(subtractResult.z, 4);

	subtractResult -= FVector3(2, 3, 4);
	ASSERT_ALMOST_EQUAL(subtractResult.x, 2);
	ASSERT_ALMOST_EQUAL(subtractResult.y, 1);
	ASSERT_ALMOST_EQUAL(subtractResult.z, 0);

	FVector3 multiplyResult = v1 * 4.f;
	ASSERT_ALMOST_EQUAL(multiplyResult.x, 8);
	ASSERT_ALMOST_EQUAL(multiplyResult.y, 12);
	ASSERT_ALMOST_EQUAL(multiplyResult.z, 16);

	multiplyResult *= 0.5f;
	ASSERT_ALMOST_EQUAL(multiplyResult.x, 4);
	ASSERT_ALMOST_EQUAL(multiplyResult.y, 4);
	ASSERT_ALMOST_EQUAL(multiplyResult.z, 4);

	FVector3 divideResult = v2 / 2;
	ASSERT_ALMOST_EQUAL(divideResult.x, 3.f);
	ASSERT_ALMOST_EQUAL(divideResult.y, 3.5f);
	ASSERT_ALMOST_EQUAL(divideResult.z, 4.f);

	divideResult /= 2;
	ASSERT_ALMOST_EQUAL(divideResult.x, 1.5f);
	ASSERT_ALMOST_EQUAL(divideResult.y, 1.75f);
	ASSERT_ALMOST_EQUAL(divideResult.z, 2.f);

	TEST_END();
}

UNIT_TEST(TestVector3Bound, "Vector3")
{
	FVector3 v(3, 4, 5);

	FVector3 cubeBound = FVector3::BoundToCube(FVector3(2, 2, 2), 2, v);
	ASSERT_ALMOST_EQUAL(v.x, 3);
	ASSERT_ALMOST_EQUAL(v.y, 4);
	ASSERT_ALMOST_EQUAL(v.z, 4);

	TEST_END();
}

UNIT_TEST(TestVector3Abs, "Vector3")
{
	FVector3 v(-3, -4, 5);

	FVector3 abs = FVector3::Abs(v);
	ASSERT_ALMOST_EQUAL(abs.x, 3);
	ASSERT_ALMOST_EQUAL(abs.y, 4);
	ASSERT_ALMOST_EQUAL(abs.z, 5);

	FVector3 sign = FVector3::GetSignVector(v);
	ASSERT_ALMOST_EQUAL(sign.x, -1);
	ASSERT_ALMOST_EQUAL(sign.y, -1);
	ASSERT_ALMOST_EQUAL(sign.z, 1);

	TEST_END();
}

FUnitTestingOutcome RunVector3Tests()
{
	return suite.RunTests();
}