#include "FPlane.h"
#include "LMath.h"

FPlane::FPlane()
{
	this->a = 1;
	this->b = 1;
	this->c = 1;
	this->d = 0;
}

FPlane::FPlane(float a, float b, float c, float d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

FPlane::FPlane(FVector3 & A, FVector3 & B, FVector3 C)
{
	FVector3 AB = B - A;
	FVector3 AC = C - A;
	FVector3 cross = FVector3::Cross(AB, AC);

	this->a = cross.x;
	this->b = cross.y;
	this->c = cross.z;
	this->d = (this->a * A.x + this->b * A.y + this->c * A.z);
}

FPlane::FPlane(const FVector4 & v)
{
	this->a = v.x;
	this->b = v.y;
	this->c = v.z;
	this->d = v.w;
}

FVector3 FPlane::Normal() const
{
	return FVector3(this->a, this->b, this->c);
}

FPlane FPlane::Normalize() const
{
	float mag = LMath::Sqrt(this->a * this->a + this->b * this->b + this->c * this->c);

	return FPlane(this->a / mag, this->b / mag, this->c / mag, this->d / mag);
}

void FPlane::Normalize(FPlane & plane)
{
	float mag = LMath::Sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);

	plane.a /= mag;
	plane.b /= mag;
	plane.c /= mag;
	plane.d /= mag;
}

float FPlane::DistanceToPoint(const FVector3 & point) const
{
	return this->a * point.x + this->b * point.y + this->c * point.z;
}

float FPlane::Halfspace(const FVector3 & point) const
{
	return DistanceToPoint(point);
}

bool FPlane::PointOnPlane(const FVector3 & point) const
{
	return DistanceToPoint(point) < 0.1f;
}
