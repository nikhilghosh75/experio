#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Math/FRect.h"

TEST_SUITE("Rect", "Experio/Math");

UNIT_TEST(TestRectGeneral, "Rect")
{
	FRect rect(0, 0, 3, 3);

	ASSERT_ALMOST_EQUAL(rect.min.x, 0);
	ASSERT_ALMOST_EQUAL(rect.min.y, 0);
	ASSERT_ALMOST_EQUAL(rect.max.x, 3);
	ASSERT_ALMOST_EQUAL(rect.max.y, 3);

	ASSERT_TRUE(rect.IsInside(FVector2(1, 1)), "");
}