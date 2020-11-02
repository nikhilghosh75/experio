#include "FVector4.h"
#include "LMath.h"

FVector4::FVector4()
{
	this->w = 0;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

FVector4::FVector4(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

FVector4::FVector4(ImVec4 V)
{
	this->w = V.w;
	this->x = V.x;
	this->y = V.y;
	this->z = V.z;
}

float FVector4::Magnitude()
{
	return LMath::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float FVector4::SqrMagnitude()
{
	return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

float FVector4::Magnitude(const FVector4 & V)
{
	return LMath::Sqrt(V.x * V.x + V.y * V.y + V.z * V.z + V.w * V.w);
}

float FVector4::SqrMagnitude(const FVector4 & V)
{
	return V.x * V.x + V.y * V.y + V.z * V.z + V.w * V.w;
}

float FVector4::Distance(const FVector4 & V)
{
	return LMath::Sqrt((this->x - V.x) * (this->x * V.x) +
		(this->y - V.y) * (this->y - V.y) +
		(this->z - V.z) * (this->z - V.z) +
		(this->w - V.w) * (this->w - V.w));
}

float FVector4::SqrDistance(const FVector4 & V)
{
	return (this->x - V.x) * (this->x * V.x) +
		(this->y - V.y) * (this->y - V.y) +
		(this->z - V.z) * (this->z - V.z) +
		(this->w - V.w) * (this->w - V.w);
}

float FVector4::Distance(const FVector4 & V1, const FVector4 V2)
{
	return LMath::Sqrt((V1.x - V2.x) * (V1.x * V2.x) +
		(V1.y - V2.y) * (V1.y - V2.y) +
		(V1.z - V2.z) * (V1.z - V2.z) +
		(V1.w - V2.w) * (V1.w - V2.w));
}

float FVector4::SqrDistance(const FVector4 & V1, const FVector4 V2)
{
	return (V1.x - V2.x) * (V1.x * V2.x) +
		(V1.y - V2.y) * (V1.y - V2.y) +
		(V1.z - V2.z) * (V1.z - V2.z) +
		(V1.w - V2.w) * (V1.w - V2.w);
}

float FVector4::Dot(const FVector4& V1, const FVector4 V2)
{
	return (V1.x * V2.x) + (V1.y * V2.y) + (V1.z * V2.z) + (V1.w * V2.w);
}

FVector4 FVector4::Abs(const FVector4 & V)
{
	return FVector4(LMath::Abs(V.w), LMath::Abs(V.x), LMath::Abs(V.y), LMath::Abs(V.z));
}

FVector4 FVector4::operator+(const FVector4 & V) const
{
	return FVector4(this->w + V.w, this->x + V.x, this->y + V.y, this->z + V.z);
}

FVector4 FVector4::operator+=(const FVector4 & V)
{
	this->w += V.w;
	this->x += V.x;
	this->y += V.y;
	this->z += V.z;
	return *this + V;
}

FVector4 FVector4::operator-(const FVector4 & V)
{
	return FVector4(this->w - V.w, this->x - V.x, this->y - V.y, this->z - V.z);
}

FVector4 FVector4::operator-=(const FVector4 & V)
{
	this->w -= V.w;
	this->x -= V.x;
	this->y -= V.y;
	this->z -= V.z;
	return *this - V;
}
