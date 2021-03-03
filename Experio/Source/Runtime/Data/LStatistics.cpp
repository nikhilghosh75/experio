#include "LStatistics.h"
#include "../Containers/Algorithm.h"
#include "../Math/LMath.h"
#include <algorithm>

float LStatistics::Average(const float * data, size_t count)
{
	return Sum(data, count) / (float)count;
}

float LStatistics::Average(const std::vector<float> data)
{
	return Sum(data.data(), data.size()) / data.size();
}

float LStatistics::CorrelationCoefficient(const float * x, const float * y, size_t count)
{
	float xMean, xStd;
	float yMean, yStd;
	MeanAndSTD(x, count, xMean, xStd);
	MeanAndSTD(y, count, yMean, yStd);

	float sum = 0.0f;
	for (size_t i = 0; i < count; i++)
	{
		float xDiff = (x[i] - xMean) / xStd;
		float yDiff = (y[i] - yMean) / yStd;
		sum += xDiff * yDiff;
	}

	return sum / (count - 1);
}

float LStatistics::CorrelationCoefficient(const std::vector<float> x, const std::vector<float> y)
{
	return CorrelationCoefficient(x.data(), y.data(), x.size());
}

float LStatistics::Max(const float * data, size_t count)
{
	float max = data[0];
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] > max) { max = data[i]; }
	}
	return max;
}

float LStatistics::Max(const std::vector<float>& data)
{
	return Max(data.data(), data.size());
}

float LStatistics::Median(float * data, size_t count)
{
	if (count % 2 == 0)
	{
		std::nth_element(data, data + (count / 2), data + count);
		std::nth_element(data, data + ((count - 1) / 2), data + count);

		return data[(count - 1) / 2] + data[count / 2];
	}
	std::nth_element(data, data + (count / 2), data + count);
	return data[count / 2];
}

float LStatistics::Median(std::vector<float>& data)
{
	return Median(data.data(), data.size());
}

float LStatistics::Min(const float * data, size_t count)
{
	float min = data[0];
	for (size_t i = 0; i < count; i++)
	{
		if (data[i] < min) { min = data[i]; }
	}
	return min;
}

float LStatistics::Min(const std::vector<float>& data)
{
	return Min(data.data(), data.size());
}

float LStatistics::Mode(const std::vector<float>& data)
{
	std::vector<std::pair<float, uint32_t>> uniqueCount = Experio::Algorithm::UniqueCount(data);
	
	float mode = uniqueCount[0].first;
	uint32_t maxCount = uniqueCount[0].second;
	for (size_t i = 1; i < uniqueCount.size(); i++)
	{
		if (uniqueCount[i].second > maxCount)
		{
			mode = uniqueCount[i].first;
			maxCount = uniqueCount[i].second;
		}
	}
	return mode;
}

std::vector<float> LStatistics::MovingAverage(const std::vector<float>& data, size_t averageSize)
{
	if (averageSize == 0 || averageSize == 1)
	{
		return data;
	}
	std::vector<float> movingAverage;
	movingAverage.reserve(data.size() - averageSize + 1);

	for (size_t i = 0; i < data.size() - averageSize + 1; i++)
	{
		float sum = 0;
		for (size_t j = 0; j < averageSize; j++)
		{
			sum += data[i + j];
		}
		movingAverage.push_back(sum / data.size());
	}

	return movingAverage;
}

float LStatistics::Percentile(const float * data, size_t count, size_t index)
{
	float elem = data[index];
	size_t lessThanCount = 0;

	for (size_t i = 0; i < count; i++)
	{
		if (data[i] < elem)
		{
			lessThanCount++;
		}
	}

	return ((float)lessThanCount * 100.f) / (count - 1);
}

float LStatistics::Percentile(const std::vector<float>& data, size_t index)
{
	return Percentile(data.data(), data.size(), index);
}

float LStatistics::Percentile(const float * data, size_t count, float elem)
{
	size_t lessThanCount = 0;
	float maxLessThan = -2000000.f;
	float minGreaterThan = 20000000.f;

	for (size_t i = 0; i < count; i++)
	{
		if (data[i] < elem)
		{
			lessThanCount++;
			if (data[i] > maxLessThan)
			{
				maxLessThan = data[i];
			}
		}
		else
		{
			if (data[i] < minGreaterThan)
			{
				minGreaterThan = data[i];
			}
		}
	}
	
	return ((float)lessThanCount + (elem - maxLessThan) / (minGreaterThan - maxLessThan)) * 100.f / count;
}

float LStatistics::Percentile(const std::vector<float>& data, float elem)
{
	return Percentile(data.data(), data.size(), elem);
}

void LStatistics::Sort(std::vector<float>& data)
{
	std::sort(data.begin(), data.begin() + data.size());
}

float LStatistics::StandardDeviation(const float * data, size_t count)
{
	float average = Average(data, count);
	
	float standardDeviation = 0;
	for (size_t i = 0; i < count; i++)
	{
		standardDeviation += (data[i] - average) * (data[i] - average);
	}

	return standardDeviation;
}

float LStatistics::StandardDeviation(const std::vector<float>& data)
{
	return StandardDeviation(data.data(), data.size());
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

float LStatistics::WeightedAverage(const float * data, const float * weights, size_t count)
{
	float sum = 0.0f;
	for (size_t i = 0; i < count; i++)
	{
		sum += data[i] * weights[i];
	}
	return sum;
}

float LStatistics::WeightedAverage(const std::vector<float>& data, const std::vector<float>& weights)
{
	return WeightedAverage(data.data(), weights.data(), weights.size());
}

void LStatistics::MeanAndSTD(const float * data, size_t count, float & average, float & std)
{
	average =  Sum(data, count) / (float)count;

	std = 0;
	for (size_t i = 0; i < count; i++)
	{
		std += (data[i] - average) * (data[i] - average);
	}
}
