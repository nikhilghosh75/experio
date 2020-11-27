#include "LStatistics.h"

float LStatistics::Average(const float * data, size_t count)
{
	return Sum(data, count) / (float)count;
}

float LStatistics::Average(const std::vector<float> data)
{
	return Sum(data.data(), data.size()) / data.size();
}

float LStatistics::Sum(const float * data, size_t count)
{
	float sum = 0.0f;
	for (size_t i = 0; i < count; i++)
	{
		sum += data[i];
	}
	return sum;
}

float LStatistics::Sum(const std::vector<float> data)
{
	return Sum(data.data(), data.size());
}
