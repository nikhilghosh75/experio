#include "FVector2.h"
#include "FVector3.h"
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

FVector2::FVector2(FVector3 V)
{
	this->x = V.x;
	this->y = V.y;
}

FVector2::FVector2(ImVec2 V)
{
	this->x = V.x;
	this->y = V.y;
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

float FVector2::Distance(const FVector2 & V1, const FVector2 & V2)
{
	return V1.Distance(V2);
}

float FVector2::SqrDistance(const FVector2 & V1, const FVector2 & V2)
{
	return V1.SqrDistance(V2);
}

FVector2 FVector2::operator+(const FVector2 Other) const
{
	return FVector2(this->x + Other.x, this->y + Other.y);
}

FVector2 FVector2::operator+=(const FVector2 Other)
{
	this->x += Other.x;
	this->y += Other.y;
	return *this + Other;
}

FVector2 FVector2::operator-(const FVector2 Other) const
{
	return FVector2(this->x - Other.x, this->y - Other.y);
}

FVector2 FVector2::operator-=(const FVector2 Other)
{
	this->x -= Other.x;
	this->y -= Other.y;
	return FVector2();
}

FVector2 FVector2::operator*(const float f) const
{
	return FVector2(this->x * f, this->y * f);
}

FVector2 FVector2::operator*=(const float f)
{
	this->x *= f;
	this->y *= f;
	return *this * f;
}

FVector2 FVector2::operator/(const float f) const
{
	return FVector2(this->x / f, this->y / f);
}

FVector2 FVector2::operator/=(const float f)
{
	this->x /= f;
	this->y /= f;
	return FVector2();
}

FVector2 FVector2::ToUVCords(const FVector2 & V)
{
	return FVector2(V.x, 1.f - V.y);
}

float FVector2::GetMax(const FVector2 & V)
{
	if (V.x > V.y)
	{
		return V.x;
	}
	return V.y;
}

float FVector2::GetMin(const FVector2 & V)
{
	if (V.x < V.y)
	{
		return V.x;
	}
	return V.y;
}

FVector2 FVector2::Abs(const FVector2 & V)
{
	return FVector2(LMath::Abs(V.x), LMath::Abs(V.y));
}

FVector2 FVector2::Reciprocal(const FVector2 & V)
{
	return FVector2(1 / V.x, 1 / V.y);
}

FVector2 FVector2::GetSignVector(const FVector2 & V)
{
	FVector2 tempVector(1, 1);
	if (V.x < 0)
	{
		tempVector.x = -1;
	}
	if (V.y < 0)
	{
		tempVector.y = -1;
	}
	return tempVector;
}

std::string FVector2::ToString(const FVector2 & V, const int numDigits)
{
	std::string xString = std::to_string(V.x);
	std::string yString = std::to_string(V.y);
	return "[" + xString + ", " + yString + "]";
}

FVector2 FVector2::Normalized() const
{
	float magnitude = this->Magnitude();
	return FVector2(this->x / magnitude, this->y / magnitude);
}

FVector2 FVector2::UVCords() const
{
	return FVector2(this->x, 1 - this->y);
}

FVector2 FVector2::Clamp(float minLength, float maxLength) const
{
	return Clamp(*this, minLength, maxLength);
}

float FVector2::GetAngle() const
{
	return LMath::Atan2(x, y);
}

float FVector2::Dot(const FVector2 & V1, const FVector2 & V2)
{
	return V1.x * V2.x + V1.y * V2.y;
}

float FVector2::Cross(const FVector2 & V1, const FVector2 & V2)
{
	return V1.x * V2.y - V1.y * V2.x;
}

FVector2 FVector2::Reflect(const FVector2 & incident, const FVector2 & normal)
{
	return incident - (normal * 2.f * Dot(incident, normal));
}

FVector2 FVector2::Refract(const FVector2 & incident, const FVector2 & normal, float indexOfRefraction)
{
	float dotValue = Dot(incident, normal);
	float k = 1.f - indexOfRefraction * indexOfRefraction * (1 - dotValue * dotValue);
	return (indexOfRefraction * incident - (indexOfRefraction * dotValue * LMath::Sqrt(k)) * normal) * (float)(k >= 0);
	return FVector2();
}

FVector2 FVector2::BoundToRect(const FVector2 & min, const FVector2 & max, const FVector2 & V)
{
	return FVector2(LMath::Clamp(V.x, min.x, min.y), LMath::Clamp(V.y, min.y, max.y));
}

FVector2 FVector2::Clamp(const FVector2 & V, float minLength, float maxLength)
{
	float sqrMagnitude = V.SqrMagnitude();
	if (sqrMagnitude > maxLength * maxLength)
	{
		return V * (maxLength / LMath::Sqrt(sqrMagnitude));
	}
	else if (sqrMagnitude < minLength * minLength)
	{
		return V * (minLength / LMath::Sqrt(sqrMagnitude));
	}
	return V;
}

FVector2 FVector2::ClampValues(const FVector2 & V, float minEntry, float maxEntry)
{
	return FVector2(LMath::Clamp(V.x, minEntry, maxEntry), LMath::Clamp(V.y, minEntry, maxEntry));
}

FVector2 operator*(float f, const FVector2 & V)
{
	return V * f;
}
