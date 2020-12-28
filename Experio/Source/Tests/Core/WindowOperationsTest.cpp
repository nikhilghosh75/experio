#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Core/LWindowOperations.h"

TEST_SUITE("WindowOperations", "Experio/Core");

UNIT_TEST(TestAspectRatio, "WindowOperations")
{
	FWindowData windowData;
	windowData.width = 960;
	windowData.height = 540;

	ASSERT_ALMOST_EQUAL(LWindowOperations::GetAspectRatio(windowData), 1.77778f);

	TEST_END();
}