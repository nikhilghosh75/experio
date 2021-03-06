#pragma once
#include <string>
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"

struct FVector3
{
public:
    float x;
    float y;
    float z;

    FVector3();
    FVector3(float x, float y, float z);
    FVector3(float x, float y);
	FVector3(glm::vec3 V);

    static float Magnitude(const FVector3& V);
    static float SqrMagnitude(const FVector3& V);

    static float Distance(const FVector3& V1, const FVector3& V2);
    static float SqrDistance(const FVector3& V1, const FVector3& V2);

    static FVector3 Normalized(const FVector3& V);

    static float Dot(const FVector3& V1, const FVector3& V2);
    static FVector3 Cross(const FVector3& V1, const FVector3& V2);
	static float Angle(const FVector3& V1, const FVector3& V2);
	static FVector3 Lerp(const FVector3& V1, const FVector3& V2, float t);
	static FVector3 Reflect(const FVector3& Incident, const FVector3& Normal);
	static FVector3 Refract(const FVector3& Incident, const FVector3& Normal, float indexOfRefraction);
	static FVector3 BoundToBox(const FVector3& Min, const FVector3& Max, const FVector3& V);
	static FVector3 BoundToCube(const FVector3& Center, float radius, const FVector3& V);
	static FVector3 Clamp(const FVector3& V, float minLength, float maxLength);
	static FVector3 ClampValues(const FVector3& V, float minEntry, float maxEntry);

    static bool Coincident(const FVector3& V1, const FVector3& V2, float Threshold=0.001f);
    static bool IsZero(const FVector3& V, float threshold=0.001f);
    static bool IsNormalized(const FVector3& V);
	static bool IsUnit(const FVector3& V);

    static float GetMax(const FVector3& V);
    static float GetMin(const FVector3& V);
    static FVector3 Abs(const FVector3& V);
    static FVector3 Reciprocal(const FVector3& V);
	static FVector3 GetSignVector(const FVector3& V);

    static std::string ToString (const FVector3& V, const int numDigits = 5);
	static glm::vec3 ToGLMVector(const FVector3& V);
	static glm::vec4 ToGLMVector4(const FVector3& V);

    operator std::string() const { return FVector3::ToString(*this); }
	operator glm::vec3() const { return ToGLMVector(*this); }
	operator glm::vec4() const { return ToGLMVector4(*this); }

	bool operator==(const FVector3& other) const;
	bool operator!=(const FVector3& other) const;

	FVector3 operator+() const;
    FVector3 operator+(const FVector3& V) const;
    FVector3 operator+=(const FVector3& V);
	FVector3 operator-() const;
    FVector3 operator-(const FVector3& V) const;
    FVector3 operator-=(const FVector3& V);
    FVector3 operator*(const float f) const;
	FVector3 operator*(const FVector3& V) const;
    FVector3 operator*=(float f);
	FVector3 operator*=(const FVector3& V);
    FVector3 operator/(const float f) const;
	FVector3 operator/(const FVector3& V);
    FVector3 operator/=(float f);
	FVector3 operator/=(const FVector3& V);

	static const FVector3 const left;
	static const FVector3 const right;
	static const FVector3 const down;
	static const FVector3 const up;
	static const FVector3 const back;
	static const FVector3 const forward;
};

FVector3 operator*(float f, const FVector3& V);