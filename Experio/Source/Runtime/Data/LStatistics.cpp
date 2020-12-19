#include "LStatistics.h"

float LStatistics::Average(const float * data, size_t count)
{
	return Sum(data, count) / (float)count;
}

float LStatistics::Average(const std::vector<float> data)
{
	return Sum(data.data(), data.size()) / data.size();
}

float LStatistics::Max(float * data, size_t count)
{
	float max = data[0];
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] > max) { max = data[i]; }
	}
	return max;
}

float LStatistics::Max(std::vector<float> data)
{
	return Max(data.data(), data.size());
}

float LStatistics::Min(float * data, size_t count)
{
	float min = data[0];
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] < min) { min = data[i]; }
	}
	return min;
}

float LStatistics::Min(std::vector<float> data)
{
	return Min(data.data(), data.size());
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

float LStatistics::WeightedAverage(float * data, float * weights, size_t count)
{
	float sum = 0.0f;
	for (size_t i = 0; i < count; i++)
	{
		sum += data[i] * weights[i];
	}
	return sum;
}

float LStatistics::WeightedAverage(std::vector<float> data, std::vector<float> weights)
{
	return WeightedAverage(data.data(), weights.data(), weights.size());
}
