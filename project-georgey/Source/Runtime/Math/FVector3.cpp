#include "FVector3.h"
#include "LMath.h"
#include <iostream>
#include <stdio.h>
using namespace std;

void TestVector()
{
    FVector3 testVector(3.0f, 4.0f);

    cout << FVector3::Magnitude(testVector) << endl; // 5
    cout << FVector3::SqrMagnitude(testVector) << endl; // 25
    cout << (string)testVector << endl;
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

FVector3 FVector3::Reflect(const FVector3 & Incident, const FVector3 & Normal)
{
	return Incident - (Normal * 2.f * Dot(Incident, Normal));
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
    if(LMath::Abs(V.x) > threshold && LMath::Abs(V.y) > threshold && LMath::Abs(V.z) > threshold)
    {
        return true;
    }
    return false;
}

bool FVector3::IsNormalized(const FVector3& V)
{
    float sqrMag = SqrMagnitude(V);
    if(sqrMag > 0.99999f && sqrMag < 1.000001f)
    {
        return true;
    }
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
	{
		tempVector.x = -1;
	}
	if (V.y < 0)
	{
		tempVector.y = -1;
	}
	if (V.z < 0)
	{
		tempVector.z = -1;
	}
	return tempVector;
}

string FVector3::ToString(const FVector3& V, const int numDigits)
{
	string xString = to_string(V.x);
	string yString = to_string(V.y);
	string zString = to_string(V.z);
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

FVector3 FVector3::operator+(const FVector3& V) const
{
    return FVector3(V.x + this->x, V.y + this->y, V.z + this->z);
}

FVector3 FVector3::operator+=(const FVector3& V)
{
    return *this + V;
}

FVector3 FVector3::operator-(const FVector3& V) const
{
    return FVector3(this->x - V.x, this->y - V.y, this->z - V.z);
}

FVector3 FVector3::operator-=(const FVector3 & V)
{
	return *this - V;
}

FVector3 FVector3::operator*(const float f) const
{
    return FVector3(this->x * f, this->y * f, this->z * f);
}

FVector3 FVector3::operator*=(float f)
{
	return *this * f;
}

FVector3 FVector3::operator/(const float f) const
{
	return FVector3();
}

FVector3 FVector3::operator/=(float f)
{
	return *this / f;
}
