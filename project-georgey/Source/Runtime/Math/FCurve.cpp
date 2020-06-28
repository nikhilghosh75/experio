#include "FCurve.h"

FCurve::FCurve(FVector2 * points, EEasingFuncType * easingTypes, unsigned int curvePointCount)
{
	this->points = points;
	this->easingTypes = easingTypes;
	this->curvePointCount = curvePointCount;
}

float FCurve::GetY(float x)
{
	// TO-DO
	return 0.0f;
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
	}
	return 0.0f;
}
