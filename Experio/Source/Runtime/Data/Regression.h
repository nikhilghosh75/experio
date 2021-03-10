#pragma once
#include <vector>

class Regression
{
public:
	virtual float Get(float x) const = 0;
};

// y = ax + b
class LinearRegression : public Regression
{
public:
	float a;
	float b;

	LinearRegression(const std::vector<float>& x, const std::vector<float>& y)
	{
		float sumX = 0;
		float sumX2 = 0;
		float sumY = 0;
		float sumXY = 0;

		for (size_t i = 0; i < x.size(); i++)
		{
			sumX += x[i];
			sumX2 += x[i] * x[i];
			sumY += y[i];
			sumXY += x[i] * y[i];
		}

		a = (sumY * sumX2 - sumX * sumXY) / (x.size() * sumX2 - sumX * sumX);
		b = (x.size() * sumXY - sumX * sumY) / (x.size() * sumX2 - sumX * sumX);
	}

	virtual float Get(float x) const override
	{
		return a * x + b;
	}
};