#pragma once
#include <vector>

class LStatistics
{
public:
	static float Average(float* data, size_t count);
	static float Average(std::vector<float> data);

	static float Max(float* data, size_t count);
	static float Max(std::vector<float> data);

	static float Median(float* data, size_t count);
	static float Median(std::vector<float> data);

	static float Min(float* data, size_t count);
	static float Min(std::vector<float> data);

	static float Mode(float* data, size_t count);
	static float Mode(std::vector<float> data);

	static float Percentile(float* data, size_t count, float elem);
	static float Percentile(std::vector<float> data, float elem);

	static float Quartile(float* data, size_t count, float elem);
	static float Quartile(std::vector<float> data, float elem);

	static float StandardDeviation(float* data, size_t count);
	static float StandardDeviation(std::vector<float> data);

	static float WeightedAverage(float* data, size_t count);
	static float WeightedAverage(std::vector<float> data);
};