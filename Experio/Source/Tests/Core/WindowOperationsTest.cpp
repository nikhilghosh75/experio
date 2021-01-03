#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Core/LWindowOperations.h"

TEST_SUITE("WindowOperations", "Experio/Core");

UNIT_TEST(TestWindowOperationAspect, "WindowOperations")
{
	FWindowData windowData;
	windowData.width = 960;
	windowData.height = 540;

	ASSERT_ALMOST_EQUAL(LWindowOperations::GetAspectRatio(windowData), 1.77778f);

	TEST_END();
}

UNIT_TEST(TestWindowOperationNormalized, "WindowOperations")
{
	FWindowData windowData;
	windowData.width = 960;
	windowData.height = 540;

	ASSERT_ALMOST_EQUAL(LWindowOperations::PixelToNormalizedSize(windowData, 24, EWindowAxisType::X), 0.025);

	TEST_END();
}