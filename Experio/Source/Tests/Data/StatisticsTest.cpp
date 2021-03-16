#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Data/LStatistics.h"

TEST_SUITE("Statistics", "Experio/Data");

UNIT_TEST(TestStatisticsAverage, "Statistics")
{
	std::vector<float> vector = { 0, 4, 5, 6, 7, 17, 20 };
	ASSERT_ALMOST_EQUAL(LStatistics::Average(vector), 8.4286f);

	TEST_END();
}

UNIT_TEST(TestStatisticsMinMax, "Statistics")
{
	std::vector<float> vector = { 9, 0, 4, 5, 6, 7, 17, 20, 11 };
	ASSERT_ALMOST_EQUAL(LStatistics::Min(vector), 0);
	ASSERT_ALMOST_EQUAL(LStatistics::Max(vector), 20);

	TEST_END();
}

UNIT_TEST(TestStatisticsMode, "Statistics")
{
	std::vector<float> vector = { 1, 1, 2, 3, 4, 5, 6 };
	ASSERT_ALMOST_EQUAL(LStatistics::Mode(vector), 1);

	TEST_END();
}