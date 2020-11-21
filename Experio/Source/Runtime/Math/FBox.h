#pragma once
#include "FVector3.h"
#include <vector>

struct FBox
{
	FVector3 min;
	FVector3 max;

	FBox();
	FBox(FVector3 min, FVector3 max);
	FBox(FVector3* points, size_t count);
	FBox(std::vector<FVector3> points);

	FVector3 ClosestPointTo(const FVector3& point) const;

	float DistanceToPoint(const FVector3& point) const;
	float SqrDistanceToPoint(const FVector3& point) const;
	
	float Volume() const;

	bool Intersect(const FBox& other) const;
	static bool Intersect(const FBox& box1, const FBox& box2);
	bool isInside(const FVector3& point) const;

	FVector3 GetCenter() const;
	FVector3 GetExtents() const;
};