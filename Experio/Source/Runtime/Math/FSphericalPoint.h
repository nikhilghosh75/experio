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
	
	static FSphericalPoint FromCenter(FVector3 point, FVector3 center);

	void Fix();

	FVector3 ToCartesianPoint() const;
	FVector3 ToCartesianPoint(const FVector3 center) const;

	FVector3 ToEulerAngles() const;

	FSphericalPoint operator+(const FSphericalPoint sp) const;
	FSphericalPoint operator+=(const FSphericalPoint sp);
	FSphericalPoint operator*(float f) const;
	FSphericalPoint operator*=(float f);

	void GetGeographicPosition(float& longitude, float& lattitude) const;

	bool InRegion(float polarStart, float polarEnd, float azimuthStart, float azimuthEnd);

	static float Distance(const FSphericalPoint sp1, const FSphericalPoint sp2);
	static float SqrDistance(const FSphericalPoint sp1, const FSphericalPoint sp2);

	static float DMSToDegrees(float degrees, float minutes, float seconds);
};