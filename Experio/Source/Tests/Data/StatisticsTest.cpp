#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Data/LStatistics.h"

TEST_SUITE("Statistics", "Experio/Data");

UNIT_TEST(TestStatisticsAverage, "Statistics")
{
	std::vector<float> vector = { 0, 4, 5, 6, 7, 17, 20 };
	ASSERT_ALMOST_EQUAL(LStatistics::Average(vector), 8.4286f);

	TEST_END();
}