#pragma once
#include <vector>

class LStatistics
{
public:
	static float Average(const float* data, size_t count);
	static float Average(const std::vector<float> data);

	static float CorrelationCoefficient(const float* x, const float* y, size_t count);
	static float CorrelationCoefficient(const std::vector<float> x, const std::vector<float> y);

	static float Max(const float* data, size_t count);
	static float Max(const std::vector<float>& data);

	static float Median(float* data, size_t count);
	static float Median(std::vector<float>& data);

	static float Min(const float* data, size_t count);
	static float Min(const std::vector<float>& data);

	static float Mode(const std::vector<float>& data);

	static std::vector<float> MovingAverage(const std::vector<float>& data, size_t averageSize);

	static float Percentile(const float* data, size_t count, size_t index);
	static float Percentile(const std::vector<float>& data, size_t index);
	static float Percentile(const float* data, size_t count, float elem);
	static float Percentile(const std::vector<float>& data, float elem);

	static void Sort(std::vector<float>& data);

	static float StandardDeviation(const float* data, size_t count);
	static float StandardDeviation(const std::vector<float>& data);

	static float Sum(const float* data, size_t count);
	static float Sum(const std::vector<float> data);

	static float WeightedAverage(const float* data, const float* weights, size_t count);
	static float WeightedAverage(const std::vector<float>& data, const std::vector<float>& weights);

private:
	static void MeanAndSTD(const float* data, size_t count, float& average, float& std);
};