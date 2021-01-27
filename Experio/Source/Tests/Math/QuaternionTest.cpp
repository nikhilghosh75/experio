#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Math/FQuaternion.h"

TEST_SUITE("Quaternion", "Experio/Math");

UNIT_TEST(TestQuaternionGeneral, "Quaternion")
{
	FQuaternion q(0, 0, 0, 1);
	ASSERT_ALMOST_EQUAL(q.x, 0);
	ASSERT_ALMOST_EQUAL(q.y, 0);
	ASSERT_ALMOST_EQUAL(q.z, 0);
	ASSERT_ALMOST_EQUAL(q.w, 0);

	TEST_END();
}