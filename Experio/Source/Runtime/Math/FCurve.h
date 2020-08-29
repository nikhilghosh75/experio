#pragma once
#include "FVector2.h"

enum class EEasingFuncType : uint8_t
{
	Linear,
	Quadratic,
	QuadIn,
	QuadOut,
	Step
};

struct FCurve
{
	unsigned int curvePointCount;
	FVector2* points;
	EEasingFuncType* easingTypes;

	FCurve();
	FCurve(FVector2* points, EEasingFuncType* easingTypes, unsigned int curvePointCount);

	float GetY(float x);

private:
	// b - start value
	// c - change in value
	// d - duration
	// t - current time
	static float GetEaseValue(float b, float c, float d, float t, EEasingFuncType easingType);
};