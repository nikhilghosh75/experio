#include "FSphericalPoint.h"
#include "LMath.h"

FSphericalPoint::FSphericalPoint()
{
	this->radius = 0;
	this->polar = 0;
	this->azimuth = 0;
}

FSphericalPoint::FSphericalPoint(float radius, float polar, float azimuth)
{
	this->radius = radius;
	this->polar = polar;
	this->azimuth = azimuth;
}

FSphericalPoint::FSphericalPoint(FVector3 point)
{
	this->radius = FVector3::Magnitude(point);
	this->polar = LMath::Acos(point.z / this->radius);
	this->azimuth = LMath::Atan(point.y / point.x);
}

void FSphericalPoint::Fix()
{
	while (this->polar > PI || this->polar < -PI)
	{
		if (this->polar > PI)
		{
			this->polar -= 2 * PI;
		}
		else
		{
			this->polar += 2 * PI;
		}
	}

	while (this->azimuth > PI || this->azimuth < -PI)
	{
		if (this->azimuth > PI)
		{
			this->azimuth -= 2 * PI;
		}
		else
		{
			this->azimuth += 2 * PI;
		}
	}
}

FVector3 FSphericalPoint::ToCartesianPoint() const
{
	return FVector3(
		this->radius * LMath::Sin(this->polar) * LMath::Cos(this->azimuth),
		this->radius * LMath::Sin(this->polar) * LMath::Sin(this->azimuth),
		this->radius * LMath::Cos(this->polar)
	);
}
