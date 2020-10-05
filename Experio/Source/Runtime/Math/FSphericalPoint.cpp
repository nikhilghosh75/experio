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

FSphericalPoint FSphericalPoint::FromCenter(FVector3 point, FVector3 center)
{
	FVector3 difference = point - center;
	return FSphericalPoint(difference);
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

FVector3 FSphericalPoint::ToCartesianPoint(const FVector3 center) const
{
	return ToCartesianPoint() + center;
}

FSphericalPoint FSphericalPoint::operator+(const FSphericalPoint sp) const
{
	return FSphericalPoint(this->radius + sp.radius, this->polar + sp.polar, this->azimuth + sp.azimuth);
}

FSphericalPoint FSphericalPoint::operator+=(const FSphericalPoint sp)
{
	this->radius += sp.radius;
	this->polar += sp.polar;
	this->azimuth += sp.azimuth;
	return *this + sp;
}

FSphericalPoint FSphericalPoint::operator*(float f) const
{
	return FSphericalPoint(this->radius * f, this->polar, this->azimuth);
}

FSphericalPoint FSphericalPoint::operator*=(float f)
{
	this->radius *= f;
	return *this * f;
}

float FSphericalPoint::Distance(const FSphericalPoint sp1, const FSphericalPoint sp2)
{
	return LMath::Sqrt(sp1.radius * sp1.radius + sp2.radius * sp2.radius -
		2 * sp1.radius * sp2.radius * 
		(LMath::Sin(sp1.polar) * LMath::Sin(sp2.polar) * LMath::Cos(sp1.azimuth - sp2.azimuth) + LMath::Cos(sp1.polar) * LMath::Cos(sp2.polar))
	);
}

float FSphericalPoint::SqrDistance(const FSphericalPoint sp1, const FSphericalPoint sp2)
{
	return sp1.radius * sp1.radius + sp2.radius * sp2.radius -
		2 * sp1.radius * sp2.radius *
		(LMath::Sin(sp1.polar) * LMath::Sin(sp2.polar) * LMath::Cos(sp1.azimuth - sp2.azimuth) + LMath::Cos(sp1.polar) * LMath::Cos(sp2.polar));
}
