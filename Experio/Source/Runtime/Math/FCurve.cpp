#include "FCurve.h"

FCurve::FCurve()
{
	this->points = nullptr;
	this->easingTypes = nullptr;
	this->curvePointCount = 0;
}

FCurve::FCurve(FVector2 * points, EEasingFuncType * easingTypes, unsigned int curvePointCount)
{
	this->points = points;
	this->easingTypes = easingTypes;
	this->curvePointCount = curvePointCount;
}

float FCurve::GetY(float x)
{
	unsigned int min = 0, max = curvePointCount;
	while (true)
	{
		unsigned int currentIndex = (min + max) / 2;
		FVector2 currentPoint = this->points[currentIndex];
		if (currentPoint.x > x)
		{
			min = currentIndex;
		}
		else if (currentPoint.x < x)
		{
			max = currentIndex;
		}

		if (min + 1 == max)
		{
			break;
		}
	}
	return GetEaseValue(
		points[min].y, points[max].y - points[min].y, points[max].x - points[min].x,
		x - points[min].x, easingTypes[min]
	);
}

float FCurve::RiemannSum(float start, float end, float delta)
{
	float sum = 0;
	for (float f = start; f < end; f += delta)
	{
		sum += GetY(f) * delta;
	}
	return sum;
}

float FCurve::GetEaseValue(float b, float c, float d, float t, EEasingFuncType easingType)
{
	switch (easingType)
	{
	case EEasingFuncType::Step:
		return b;
	case EEasingFuncType::Linear:
		return b + (c * t / d);
	case EEasingFuncType::QuadIn:
		return c * (t / d) * (t / d) + b;
	case EEasingFuncType::QuadOut:
		return  -c * (t / d) * ((t / d) - 2) + b;
	}
	return 0.0f;
}
