#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Data/LStatistics.h"

TEST_SUITE("Statistics", "Experio/Data");

UNIT_TEST(TestStatisticsAverage, "Statistics")
{
	std::vector<float> vector = { 0, 4, 5, 6, 7, 17, 20 };
	ASSERT_ALMOST_EQUAL(LStatistics::Sum(vector), 59);
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

UNIT_TEST(TestStatisticsWeightedAverage, "Statistics")
{
	std::vector<float> values = { 0.9, 0.8, 0.6, 0.4, 0.92, 0.85 };
	std::vector<float> weights = { 10, 10, 20, 30, 15, 15 };
	ASSERT_ALMOST_EQUAL(LStatistics::WeightedAverage(values, weights), 67.55);

	TEST_END();
}

UNIT_TEST(TestStatisticsCorrelation, "Statistics")
{
	std::vector<float> x = { 1, 2, 3, 4, 5, 6, 7 };
	std::vector<float> y = { 8, 25, 45, 90, 80, 80, 105 };

	ASSERT_ALMOST_EQUAL(LStatistics::CorrelationCoefficient(x, y), 0.930);

	TEST_END();
}

UNIT_TEST(TestStatisticsPercentile, "Statistics")
{
	std::vector<float> data = { 5, 10, 20, 25, 40, 55, 60, 70 };

	ASSERT_ALMOST_EQUAL(LStatistics::Percentile(data, 14.f), 20);
	ASSERT_ALMOST_EQUAL(LStatistics::Percentile(data, (size_t)3), 37.5f);

	TEST_END();
}

UNIT_TEST(TestStatisticsSTD, "Statistics")
{
	std::vector<float> data = { 5, 10, 20, 25, 40, 55, 60, 70 };

	ASSERT_ALMOST_EQUAL(LStatistics::StandardDeviation(data), 22.70f);

	TEST_END();
}

UNIT_TEST(TestStatisticsMovingAverage, "Statistics")
{
	std::vector<float> data = { 2, 4, 6, 8, 12, 14, 16, 18, 20 };

	std::vector<float> movingAverage = LStatistics::MovingAverage(data, 4);

	ASSERT_EQUAL(movingAverage.size(), 6, "");

	ASSERT_ALMOST_EQUAL(movingAverage[0], 5);
	ASSERT_ALMOST_EQUAL(movingAverage[1], 7.5);
	ASSERT_ALMOST_EQUAL(movingAverage[2], 10);
	ASSERT_ALMOST_EQUAL(movingAverage[3], 12.5);
	ASSERT_ALMOST_EQUAL(movingAverage[4], 15);
	ASSERT_ALMOST_EQUAL(movingAverage[5], 17);
}