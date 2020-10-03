#pragma once
#include "FVector3.h"

struct FSphericalPoint
{
	float radius;
	float polar;
	float azimuth;

	FSphericalPoint();
	FSphericalPoint(float radius, float polar, float azimuth);
	FSphericalPoint(FVector3 point);

	void Fix();

	FVector3 ToCartesianPoint() const;
};