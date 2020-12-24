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