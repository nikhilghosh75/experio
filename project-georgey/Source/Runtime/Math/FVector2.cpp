#include "FVector2.h"
#include "LMath.h"

FVector2::FVector2()
{
	this->x = 0;
	this->y = 0;
}

FVector2::FVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float FVector2::Magnitude() const
{
	return LMath::Sqrt(this->x * this->x + this->y * this->y);
}

float FVector2::SqrMagnitude() const
{
	return this->x * this->x + this->y * this->y;
}

float FVector2::Distance(const FVector2 & V) const
{
	return LMath::Sqrt((V.x - this->x) * (V.x - this->x) + (V.y - this->y) * (V.y - this->y));
}

float FVector2::SqrDistance(const FVector2 & V) const
{
	return (V.x - this->x) * (V.x - this->x) + (V.y - this->y) * (V.y - this->y);
}

FVector2 FVector2::operator+(const FVector2 Other) const
{
	return FVector2(this->x + Other.x, this->y + Other.y);
}

FVector2 FVector2::operator+=(const FVector2 Other)
{
	return FVector2(this->x + Other.x, this->y + Other.y);
}

FVector2 FVector2::operator-(const FVector2 Other) const
{
	return FVector2(this->x - Other.x, this->y - Other.y);
}

FVector2 FVector2::ToUVCords(const FVector2 & V)
{
	return FVector2(V.x, 1.f - V.y);
}

FVector2 FVector2::UVCords() const
{
	return FVector2(this->x, 1 - this->y);
}

float FVector2::Dot(const FVector2 & V1, const FVector2 & V2)
{
	return V1.x * V2.x + V1.y * V2.y;
}

float FVector2::Cross(const FVector2 & V1, const FVector2 & V2)
{
	return V1.x * V2.y - V1.y * V2.x;
}
