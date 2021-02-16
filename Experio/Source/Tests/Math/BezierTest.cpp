#include "Runtime/Math/Bezier.h"
#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"

TEST_SUITE("Bezier", "Experio/Math");

UNIT_TEST(TestBezierGeneral, "Bezier")
{
	Bezier bezier;
	bezier.Insert(0, 0, 5, 6);
	bezier.Insert(5, 6, 7, 3);
	bezier.Insert(4, 3, 5, 6);
	bezier.Insert(9, 4, 10, 5);
}
