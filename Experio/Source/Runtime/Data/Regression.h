#pragma once
#include <vector>

/// <summary>
/// A series of regression types to calculate 
/// </summary>

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

// y = ax^2 + bx + c
class QuadraticRegression : public Regression
{
public:
	float a;
	float b;
	float c;

	QuadraticRegression(const std::vector<float>& x, const std::vector<float>& y)
	{
		unsigned int n = x.size();
		float sumX = 0;
		float sumX2 = 0;
		float sumX2Y = 0;
		float sumXY = 0;
		float sumX3 = 0;
		float sumY = 0;
		float sumX4 = 0;

		for (size_t i = 0; i < x.size(); i++)
		{
			sumX += x[i];
			sumX2 += x[i] * x[i];
			sumX3 += x[i] * x[i] * x[i];
			sumX4 += x[i] * x[i] * x[i] * x[i];
			sumY += y[i];
			sumXY += x[i] * y[i];
			sumX2Y += x[i] * x[i] * y[i];
		}

		// ADD STUFF LATER
	}
};