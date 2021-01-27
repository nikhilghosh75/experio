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

	FPlane(FVector3& A, FVector3& B, FVector3 C);

	FPlane(const FVector4& v);

	FVector3 Normal() const;

	FPlane Normalize() const;

	static void Normalize(FPlane& plane);

	float DistanceToPoint(const FVector3& point) const;

	float Halfspace(const FVector3& point) const;

	bool PointOnPlane(const FVector3& point) const;
};