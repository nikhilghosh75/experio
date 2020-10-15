#pragma once
#include "FVector3.h"

struct FRay
{
	FVector3 origin;
	FVector3 direction;

	FRay();
	FRay(FVector3 origin, FVector3 direction);

	static FRay BetweenPoints(FVector3 start, FVector3 end);

	float DistanceToPoint(FVector3 point) const;
	float SqrDistanceToPoint(FVector3 point) const;

	FVector3 ClosestPoint(FVector3 point) const;

	FVector3 PointAt(float distance) const;
};