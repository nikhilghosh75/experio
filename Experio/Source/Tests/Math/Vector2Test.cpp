#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Math/FVector2.h"

TEST_SUITE("Vector2", "Experio/Math");

UNIT_TEST(TestVector2Magnitude, "Vector2")
{
	FVector2 v(3, 4);
	ASSERT_ALMOST_EQUAL(v.Magnitude(), 5);
	ASSERT_ALMOST_EQUAL(v.SqrMagnitude(), 25);

	TEST_END();
}

UNIT_TEST(TestVector2Normalized, "Vector2")
{
	FVector2 v(6, 8);
	FVector2 normalized = v.Normalized();

	ASSERT_FALSE(v.IsNormalized(), "");
	ASSERT_TRUE(normalized.IsNormalized(), "");

	ASSERT_ALMOST_EQUAL(normalized.x, 0.6f);
	ASSERT_ALMOST_EQUAL(normalized.y, 0.8f);

	TEST_END();
}

UNIT_TEST(TestVector2Zero, "Vector2")
{
	FVector2 v(1, 2);
	FVector2 zero(0, 0);

	ASSERT_FALSE(v.IsZero(), "");
	ASSERT_TRUE(zero.IsZero(), "");
	
	ASSERT_ALMOST_EQUAL(zero.SqrMagnitude(), 0);

	TEST_END();
}

UNIT_TEST(TestVector2Products, "Vector2")
{
	FVector2 v1(1, 2);
	FVector2 v2(3, 4);

	ASSERT_ALMOST_EQUAL(FVector2::Dot(v1, v2), 11);
	ASSERT_ALMOST_EQUAL(FVector2::Cross(v1, v2), -2);

	TEST_END();
}

UNIT_TEST(TestVector2Operators, "Vector2")
{
	FVector2 v1(1, 2);
	FVector2 v2(3, 4);

	FVector2 addResult = v1 + v2;
	FVector2 subResult = v1 - v2;

	ASSERT_ALMOST_EQUAL(addResult.x, 4);
	ASSERT_ALMOST_EQUAL(addResult.y, 6);

	ASSERT_ALMOST_EQUAL(subResult.x, -2);
	ASSERT_ALMOST_EQUAL(subResult.y, -2);

	FVector2 multiplyResult = v2 * 5.f;

	ASSERT_ALMOST_EQUAL(multiplyResult.x, 5);
	ASSERT_ALMOST_EQUAL(multiplyResult.y, 10);

	TEST_END();
}

UNIT_TEST(TestVector2Distance, "Vector2")
{
	FVector2 v1(1, 2);
	FVector2 v2(4, -2);

	ASSERT_EQUAL(FVector2::Distance(v1, v2), 5.f, "");
	ASSERT_EQUAL(FVector2::SqrDistance(v1, v2), 25.f, "");

	TEST_END();
}

UNIT_TEST(TestVector2Abs, "Vector")
{
	FVector2 v(4, -5);

	ASSERT_ALMOST_EQUAL(FVector2::Abs(v).x, 4);
	ASSERT_ALMOST_EQUAL(FVector2::Abs(v).x, 5);

	TEST_END();
}