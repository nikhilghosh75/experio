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

void FRect::Fix()
{
	if (min.x > max.x)
	{
		float temp = min.x;
		min.x = max.x;
		max.x = temp;
	}
	if (min.y > max.y)
	{
		float temp = min.y;
		min.y = max.y;
		max.y = temp;
	}
}

bool FRect::IsInside(FVector2 point) const
{
	return (point.x > min.x) && (point.y > min.y) && (point.x < max.x) && (point.y < min.y);
}

FVector2 FRect::GetTopLeft() const
{
	return FVector2(min.x, max.y);
}

FVector2 FRect::GetTopRight() const
{
	return max;
}

FVector2 FRect::GetBottomLeft() const
{
	return min;
}

FVector2 FRect::GetBottomRight() const
{
	return FVector2(max.x, min.y);
}

float FRect::GetWidth() const
{
	return max.x - min.x;
}

float FRect::GetHeight() const
{
	return max.y - min.y;
}

float FRect::GetArea() const
{
	return GetHeight() * GetWidth();
}

FVector2 FRect::GetCenter() const
{
	return FVector2( (max.x - min.x) / 2.f, (max.y - min.y) / 2.f );
}
