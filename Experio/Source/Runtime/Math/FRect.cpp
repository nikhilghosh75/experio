#include "FRect.h"
#include "LMath.h"

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

FRect::FRect(const FVector2 * points, int count)
{
	this->min = FVector2(100000, 100000);
	this->max = FVector2(-100000, -100000);

	for (int i = 0; i < count; i++)
	{
		if (points[i].x < min.x)
		{
			min.x = points[i].x;
		}
		
		if (points[i].y < min.y)
		{
			min.y = points[i].y;
		}

		if (points[i].x > max.x)
		{
			max.x = points[i].x;
		}

		if (points[i].y > max.y)
		{
			max.y = points[i].y;
		}
	}
}

FRect::FRect(const std::vector<FVector2> points)
{
	this->min = FVector2(100000, 100000);
	this->max = FVector2(-100000, -100000);

	for (int i = 0; i < points.size(); i++)
	{
		if (points[i].x < min.x)
		{
			min.x = points[i].x;
		}

		if (points[i].y < min.y)
		{
			min.y = points[i].y;
		}

		if (points[i].x > max.x)
		{
			max.x = points[i].x;
		}

		if (points[i].y > max.y)
		{
			max.y = points[i].y;
		}
	}
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

FVector2 & FRect::operator[](int i)
{
	if (i == 0)
	{
		return this->min;
	}
	return this->max;
}

float FRect::GetDistanceToPoint(const FVector2 & point) const
{
	if (point.x < min.x)
	{
		if (point.y < min.y)
		{
			return FVector2::Distance(point, min);
		}
		else if (point.y > max.y)
		{
			return FVector2::Distance(point, FVector2(min.x, max.y));
		}
		return min.x - point.x;
	}
	else if(point.x > max.x)
	{
		if (point.y < min.y)
		{
			return FVector2::Distance(point, FVector2(max.x, min.y));
		}
		else if (point.y > max.y)
		{
			return FVector2::Distance(point, max);
		}
		return point.x - max.x;
	}
	
	if (point.y > max.y)
	{
		return point.y - max.y;
	}
	else if (point.y < min.y)
	{
		return min.y - point.y;
	}
	return 0.0f;
}

float FRect::GetArea() const
{
	return GetHeight() * GetWidth();
}

FVector2 FRect::GetCenter() const
{
	return FVector2( (max.x - min.x) / 2.f, (max.y - min.y) / 2.f );
}

FVector2 FRect::GetClosestPointOnRect(const FVector2 point) const
{
	if (point.x < min.x)
	{
		if (point.y < min.y)
		{
			return min;
		}
		else if (point.y > max.y)
		{
			return FVector2(min.x, max.y);
		}
		return FVector2(min.x, point.y);
	}
	else if (point.x > max.x)
	{
		if (point.y < min.y)
		{
			return FVector2(max.x, min.y);
		}
		else if (point.y > max.y)
		{
			return max;
		}
		return FVector2(max.x, point.y);
	}

	if (point.y > max.y)
	{
		return FVector2(point.x, max.y);
	}
	else if (point.y < min.y)
	{
		return FVector2(point.x, min.y);
	}
	return point;
}

bool FRect::Intersecting(const FRect & other) const
{
	if (this->max.x < other.min.x)
	{
		return false;
	}
	if (this->min.x > other.max.x)
	{
		return false;
	}
	if (this->max.y < other.min.y)
	{
		return false;
	}
	if (this->min.y > other.max.y)
	{
		return false;
	}
	return true;
}

bool FRect::Intersecting(const FRect & R1, const FRect R2)
{
	return R1.Intersecting(R2);
}

bool FRect::IsInside(const FVector2 & other) const
{
	return (other.x > min.x && other.x < max.x) && (other.y > min.y && other.y < max.y);
}
