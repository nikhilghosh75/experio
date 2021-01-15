#pragma once
#include "FVector3.h"
#include "FVector4.h"

// Represented as ax + by + cz = d
struct FPlane
{
	float a;
	float b;
	float c;
	float d;

	FPlane();

	FPlane(float a, float b, float c, float d);

	FPlane(const FVector4& v);

	FPlane Normalized() const;

	float DistanceToPoint(const FVector3& point) const;

	bool PointOnPlane(const FVector3& point) const;
};