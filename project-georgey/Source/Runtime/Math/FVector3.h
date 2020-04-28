#pragma once
#include <string>
using namespace std;

#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/glm.hpp"
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/mat4x4.hpp"

struct FVector3
{
public:
    float x;
    float y;
    float z;

    FVector3();
    FVector3(float x, float y, float z);
    FVector3(float x, float y);

    static float Magnitude(const FVector3& V);
    static float SqrMagnitude(const FVector3& V);

    static float Distance(const FVector3& V1, const FVector3& V2);
    static float SqrDistance(const FVector3& V1, const FVector3& V2);

    static FVector3 Normalized(const FVector3& V);

    static float Dot(const FVector3& V1, const FVector3& V2);
    static FVector3 Cross(const FVector3& V1, const FVector3& V2);
	static FVector3 Reflect(const FVector3& Incident, const FVector3& Normal);
	static FVector3 Refract(const FVector3& Incident, const FVector3& Normal, float indexOfRefraction);

    static bool Coincident(const FVector3& V1, const FVector3& V2, float Threshold=0.001f);
    static bool IsZero(const FVector3& V, float threshold=0.001f);
    static bool IsNormalized(const FVector3& V);

    static float GetMax(const FVector3& V);
    static float GetMin(const FVector3& V);
    static FVector3 Abs(const FVector3& V);
    static FVector3 Reciprocal(const FVector3& V);
	static FVector3 GetSignVector(const FVector3& V);

    static string ToString (const FVector3& V, const int numDigits = 5);
	static glm::vec3 ToGLMVector(const FVector3& V);

    operator string() const { return FVector3::ToString(*this); }
	operator glm::vec3() const { return ToGLMVector(*this); }

    FVector3 operator+(const FVector3& V) const;
    FVector3 operator+=(const FVector3& V);
    FVector3 operator-(const FVector3& V) const;
    FVector3 operator-=(const FVector3& V);
    FVector3 operator*(const float f) const;
    FVector3 operator*=(float f);
    FVector3 operator/(const float f) const;
    FVector3 operator/=(float f);
};