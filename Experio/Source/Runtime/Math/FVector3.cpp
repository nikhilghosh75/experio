#include "FVector3.h"
#include "LMath.h"
#include <iostream>

void TestVector()
{
    FVector3 testVector(3.0f, 4.0f);

	std::cout << FVector3::Magnitude(testVector) << std::endl; // 5
	std::cout << FVector3::SqrMagnitude(testVector) << std::endl; // 25
	std::cout << (std::string)testVector << std::endl;
}

FVector3::FVector3()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

FVector3::FVector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

FVector3::FVector3(float x, float y)
{
    this->x = x;
    this->y = y;
    this->z = 0.0f;
}

FVector3::FVector3(glm::vec3 V)
{
	this->x = V.x;
	this->y = V.y;
	this->z = V.z;
}

float FVector3::Magnitude(const FVector3& v)
{
    return LMath::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float FVector3::SqrMagnitude(const FVector3& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float FVector3::Distance(const FVector3& V1, const FVector3& V2)
{
    return LMath::Sqrt((V1.x - V2.x) * (V1.x - V2.x) + (V1.y - V2.y) * (V1.y - V2.y) + (V1.z - V2.z) * (V1.z - V2.z));
}

float FVector3::SqrDistance(const FVector3& V1, const FVector3& V2)
{
    return (V1.x - V2.x) * (V1.x - V2.x) + (V1.y - V2.y) * (V1.y - V2.y) + (V1.z - V2.z) * (V1.z - V2.z);
}

FVector3 FVector3::Normalized(const FVector3& V)
{
    float magnitude = Magnitude(V);
    return FVector3(V.x / magnitude, V.y / magnitude, V.z / magnitude);
}

float FVector3::Dot(const FVector3& V1, const FVector3& V2)
{
    return (V1.x * V2.x) + (V1.y * V2.y) + (V1.z * V2.z);
}

FVector3 FVector3::Cross(const FVector3& V1, const FVector3& V2)
{
    return FVector3(V1.y * V2.z - V1.z * V2.y, V1.z * V2.x - V1.x * V2.z, V1.x * V2.y - V1.y * V2.x);
}

FVector3 FVector3::Lerp(const FVector3 & V1, const FVector3 & V2, float t)
{
	return FVector3(
		LMath::Lerp(V1.x, V2.x, t),
		LMath::Lerp(V1.y, V2.y, t),
		LMath::Lerp(V1.z, V2.z, t)
	);
}

FVector3 FVector3::Reflect(const FVector3 & Incident, const FVector3 & Normal)
{
	return Incident - (Normal * 2.f * Dot(Incident, Normal));
}

FVector3 FVector3::Refract(const FVector3 & Incident, const FVector3 & Normal, float indexOfRefraction)
{
	float dotValue = Dot(Incident, Normal);
	float k = 1.f - indexOfRefraction * indexOfRefraction * (1 - dotValue * dotValue);
	return (indexOfRefraction * Incident - (indexOfRefraction * dotValue * LMath::Sqrt(k)) * Normal) * (float)(k >= 0);
}

FVector3 FVector3::BoundToBox(const FVector3 & Min, const FVector3 & Max, const FVector3 & V)
{
	return FVector3(LMath::Clamp(V.x, Min.x, Max.x), LMath::Clamp(V.y, Min.y, Max.y), LMath::Clamp(V.z, Min.z, Max.z));
}

FVector3 FVector3::BoundToCube(const FVector3 & Center, float radius, const FVector3 & V)
{
	return BoundToBox(Center - FVector3(radius, radius, radius), Center + FVector3(radius, radius, radius), V);
}

FVector3 FVector3::Clamp(const FVector3 & V, float minLength, float maxLength)
{
	float sqrMagnitude = FVector3::SqrMagnitude(V);
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

FVector3 FVector3::ClampValues(const FVector3 & V, float minEntry, float maxEntry)
{
	return FVector3(LMath::Clamp(V.x, minEntry, maxEntry), LMath::Clamp(V.y, minEntry, maxEntry), LMath::Clamp(V.z, minEntry, maxEntry));
}


bool FVector3::Coincident(const FVector3& V1, const FVector3& V2, float threshold)
{
    if(Dot(V1, V2) < threshold)
    {
        return true;
    }
    return false;
}

bool FVector3::IsZero(const FVector3& V, float threshold)
{
    if(LMath::Abs(V.x) > threshold || LMath::Abs(V.y) > threshold || LMath::Abs(V.z) > threshold)
    {
        return false;
    }
    return true;
}

bool FVector3::IsNormalized(const FVector3& V)
{
    float sqrMag = SqrMagnitude(V);
    if(sqrMag > 0.99999f && sqrMag < 1.000001f)
        return true;
    return false;
}

bool FVector3::IsUnit(const FVector3 & V)
{
	return LMath::ApproxEquals(SqrMagnitude(V), 1.f);
}

float FVector3::GetMax(const FVector3& V)
{
    float max = V.x;
    if(V.y > max)
    {
        max = V.y;
    }
    if(V.z > max)
    {
        max = V.z;
    }
    return max;
}

float FVector3::GetMin(const FVector3& V)
{
    float min = V.x;
    if(V.y < min)
    {
        min = V.y;
    }
    if(V.z < min)
    {
        min = V.z;
    }
    return min;
}

FVector3 FVector3::Abs(const FVector3& V)
{
    return FVector3(LMath::Abs(V.x), LMath::Abs(V.y), LMath::Abs(V.z));
}

FVector3 FVector3::Reciprocal(const FVector3& V)
{
    return FVector3(1.f/V.x, 1.f/V.y, 1.f/V.z);
}

FVector3 FVector3::GetSignVector(const FVector3 & V)
{
	FVector3 tempVector(1, 1, 1);
	if (V.x < 0)
		tempVector.x = -1;
	if (V.y < 0)
		tempVector.y = -1;
	if (V.z < 0)
		tempVector.z = -1;
	return tempVector;
}

std::string FVector3::ToString(const FVector3& V, const int numDigits)
{
	std::string xString = std::to_string(V.x);
	std::string yString = std::to_string(V.y);
	std::string zString = std::to_string(V.z);
    return "[" + xString + ", " + yString + ", " + zString + "]";
}

glm::vec3 FVector3::ToGLMVector(const FVector3 & V)
{
	// Directly cast the current vector into a glm::vec3 type
	glm::vec3 tempVector = *(glm::vec3*)&V;
	return tempVector;
}

glm::vec4 FVector3::ToGLMVector4(const FVector3 & V)
{
	return glm::vec4(V.x, V.y, V.z, 0.f);
}

bool FVector3::operator==(const FVector3 & other) const
{
	return LMath::ApproxEquals(this->x, other.x) && LMath::ApproxEquals(this->y, other.y)
		&& LMath::ApproxEquals(this->z, other.z);
}

bool FVector3::operator!=(const FVector3 & other) const
{
	return !LMath::ApproxEquals(this->x, other.x) || !LMath::ApproxEquals(this->y, other.y)
		|| !LMath::ApproxEquals(this->z, other.z);
}

FVector3 FVector3::operator+() const
{
	return FVector3(this->x, this->y, this->z);
}

FVector3 FVector3::operator+(const FVector3& V) const
{
    return FVector3(V.x + this->x, V.y + this->y, V.z + this->z);
}

FVector3 FVector3::operator+=(const FVector3& V)
{
	this->x += V.x;
	this->y += V.y;
	this->z += V.z;
    return *this + V;
}

FVector3 FVector3::operator-() const
{
	return FVector3(-this->x, -this->y, -this->z);
}

FVector3 FVector3::operator-(const FVector3& V) const
{
    return FVector3(this->x - V.x, this->y - V.y, this->z - V.z);
}

FVector3 FVector3::operator-=(const FVector3 & V)
{
	this->x -= V.x;
	this->y -= V.y;
	this->z -= V.z;
	return *this - V;
}

FVector3 FVector3::operator*(const float f) const
{
    return FVector3(this->x * f, this->y * f, this->z * f);
}

FVector3 FVector3::operator*(const FVector3 & V) const
{
	return FVector3(this->x * V.x, this->y * V.y, this->z * V.z);
}

FVector3 FVector3::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this * f;
}

FVector3 FVector3::operator*=(const FVector3 & V)
{
	this->x *= V.x;
	this->y *= V.y;
	this->z *= V.z;
	return *this * V;
}

FVector3 FVector3::operator/(const float f) const
{
	return FVector3(this->x / f, this->y / f, this->z / f);
}

FVector3 FVector3::operator/(const FVector3 & V)
{
	return FVector3(this->x / V.x, this->y / V.y, this->z / V.z);
}

FVector3 FVector3::operator/=(float f)
{
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this / f;
}

FVector3 FVector3::operator/=(const FVector3 & V)
{
	this->x / V.x;
	this->y / V.y;
	this->z / V.z;
	return *this / V;
}

FVector3 operator*(float f, const FVector3 & V)
{
	return FVector3(f * V.x, f * V.y, f * V.z);
}
