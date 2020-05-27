#include "FRect.h"

FRect::FRect()
{
	this->min = FVector2(-1.f, -1.f);
	this->max = FVector2(1.f, 1.f);
}

FRect::FRect(FVector2 min, FVector2 max)
{
	this->min = min;
	this->max = max;
}

FRect::FRect(float minX, float minY, float maxX, float maxY)
{
	this->min = FVector2(minX, minY);
	this->max = FVector2(maxX, maxY);
}

bool FRect::IsInside(FVector2 point)
{
	return (point.x > min.x) && (point.y > min.y) && (point.x < max.x) && (point.y < min.y);
}
