#pragma once
#include "FVector2.h"
#include <vector>

struct FRect
{
	FVector2 min;
	FVector2 max;

	FRect();
	FRect(FVector2 min, FVector2 max);
	FRect(float minX, float minY, float maxX, float maxY);
	FRect(const FVector2* points, int count); // Creates a bounding box
	FRect(const std::vector<FVector2> points);

	void Fix();

	bool operator == (const FRect& other) const { return (min == other.min) && (max == other.max); }
	bool operator != (const FRect& other) const { return !(min == other.min) || !(max == other.max); }

	bool IsInside(FVector2 point) const;

	FVector2 GetTopLeft() const;
	FVector2 GetTopRight() const;
	FVector2 GetBottomLeft() const;
	FVector2 GetBottomRight() const;

	float GetWidth() const;
	float GetHeight() const;

	FVector2& operator[](int i);

	// +, +=

	// DistanceToPoint
	// ExpandBy
	
	float GetArea() const;

	FVector2 GetCenter() const;
	
	// Event
	// Intersect
	// IsInside
	// Closest Point
};