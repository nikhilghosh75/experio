#include "FBox.h"

FBox::FBox()
{
	this->min = FVector3(0, 0, 0);
	this->max = FVector3(0, 0, 0);
}

FBox::FBox(FVector3 min, FVector3 max)
{
	this->min = min;
	this->max = max;
}

FBox::FBox(FVector3 * points, size_t count)
{
	this->min = FVector3(1000000, 1000000, 1000000);
	this->max = FVector3(-1000000, -1000000, -1000000);

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

		if (points[i].z < min.z)
		{
			min.z = points[i].z;
		}

		if (points[i].x > max.x)
		{
			max.x = points[i].x;
		}

		if (points[i].y > max.y)
		{
			max.y = points[i].y;
		}

		if (points[i].z > max.z)
		{
			max.z = points[i].z;
		}
	}
}

FBox::FBox(std::vector<FVector3> points)
{
	this->min = FVector3(1000000, 1000000, 1000000);
	this->max = FVector3(-1000000, -1000000, -1000000);

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

		if (points[i].z < min.z)
		{
			min.z = points[i].z;
		}

		if (points[i].x > max.x)
		{
			max.x = points[i].x;
		}

		if (points[i].y > max.y)
		{
			max.y = points[i].y;
		}

		if (points[i].z > max.z)
		{
			max.z = points[i].z;
		}
	}
}

FVector3 FBox::ClosestPointTo(const FVector3 & point) const
{
	FVector3 closestPoint = point;

	if (point.x < min.x)
	{
		closestPoint.x = min.x;
	}
	else if (point.x > max.x)
	{
		closestPoint.x = max.x;
	}

	if (point.y < min.y)
	{
		closestPoint.y = min.y;
	}
	else if (point.y > max.y)
	{
		closestPoint.y = max.y;
	}

	if (point.z < min.z)
	{
		closestPoint.z = min.z;
	}
	else if (point.z > max.z)
	{
		closestPoint.z = max.z;
	}

	return closestPoint;
}

float FBox::DistanceToPoint(const FVector3 & point) const
{
	return FVector3::Distance(point, ClosestPointTo(point));
}

float FBox::SqrDistanceToPoint(const FVector3 & point) const
{
	return FVector3::SqrDistance(point, ClosestPointTo(point));
}

float FBox::Volume() const
{
	return (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
}

bool FBox::Intersect(const FBox & other) const
{
	if ((min.x > other.max.x) || (other.min.x > max.x))
	{
		return false;
	}
	if ((min.y > other.max.y) || (other.min.y > max.y))
	{
		return false;
	}
	if ((min.z > other.max.z) || (other.min.z > max.z))
	{
		return false;
	}
	return true;
}

bool FBox::Intersect(const FBox & box1, const FBox & box2)
{
	if ((box1.min.x > box2.max.x) || (box2.min.x > box1.max.x))
	{
		return false;
	}
	if ((box1.min.y > box2.max.y) || (box2.min.y > box1.max.y))
	{
		return false;
	}
	if ((box1.min.z > box2.max.z) || (box2.min.z > box1.max.z))
	{
		return false;
	}
	return true;
}

bool FBox::isInside(const FVector3 & point) const
{
	return (point.x > min.x && point.x < max.x) 
		&& (point.y > min.y && point.y < max.y)
		&& (point.z > min.z && point.z < max.z);
}

FVector3 FBox::GetCenter() const
{
	return (max + min) / 2;
}

FVector3 FBox::GetExtents() const
{
	return max - min;
}
