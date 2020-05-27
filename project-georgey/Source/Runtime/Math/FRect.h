#pragma once
#include "FVector2.h"

struct FRect
{
	FVector2 min;

	FVector2 max;

	FRect();
	FRect(FVector2 min, FVector2 max);
	FRect(float minX, float minY, float maxX, float maxY);
	FRect(const FVector2* points, int count); // Creates a bounding box

	bool operator == (const FRect& other) const { return (min == other.min) && (max == other.max); }

	bool IsInside(FVector2 point);
	// !=
	// +, +=
	// []

	// DistanceToPoint
	// ExpandBy
	// Area
	// Center
	// Event
	// Intersect
	// IsInside
	// Closest Point
};