#include "FRay.h"

FRay::FRay()
{
	this->origin = FVector3(0, 0, 0);
	this->direction = FVector3(1, 0, 0);
}

FRay::FRay(FVector3 origin, FVector3 direction)
{
	this->origin = origin;
	this->direction = FVector3::Normalized(direction);
}

FRay FRay::BetweenPoints(FVector3 start, FVector3 end)
{
	return FRay(start, end - start);
}

float FRay::DistanceToPoint(FVector3 point) const
{
	float rayParam = FVector3::Dot(point - origin, direction);
	if (rayParam < 0)
	{
		return FVector3::Distance(origin, point);
	}
	FVector3 projectedPoint = origin + rayParam * direction;
	return FVector3::Distance(projectedPoint, point);
}

float FRay::SqrDistanceToPoint(FVector3 point) const
{
	float rayParam = FVector3::Dot(point - origin, direction);
	if (rayParam < 0)
	{
		return FVector3::SqrDistance(origin, point);
	}
	FVector3 projectedPoint = origin + rayParam * direction;
	return FVector3::SqrDistance(projectedPoint, point);
}

FVector3 FRay::ClosestPoint(FVector3 point) const
{
	float rayParam = FVector3::Dot(point - origin, direction);
	if (rayParam < 0)
	{
		return origin;
	}
	return origin + rayParam * direction;
}

FVector3 FRay::PointAt(float distance) const
{
	return origin + distance * direction;
}
