#pragma once
#include <string>
#include "glm/glm.hpp"
#include "imgui.h"

class FVector3;

struct FVector2
{
	float x;
	float y;

	FVector2();
	FVector2(float x, float y);
	FVector2(FVector3 V);
	FVector2(ImVec2 V);

	float Magnitude() const;
	float SqrMagnitude() const;
	float Distance(const FVector2& V) const;
	float SqrDistance(const FVector2& V) const;

	static float Distance(const FVector2& V1, const FVector2& V2);
	static float SqrDistance(const FVector2& V1, const FVector2& V2);

	bool IsNormalized() const;
	bool IsZero() const;
	bool IsUnit() const;

	FVector2 Normalized() const;
	FVector2 UVCords() const;
	FVector2 Clamp(float minLength, float maxLength) const;
	float GetAngle() const;

	static float Dot(const FVector2& V1, const FVector2& V2);
	static float Cross(const FVector2& V1, const FVector2& V2);
	static FVector2 Reflect(const FVector2& incident, const FVector2& normal);
	static FVector2 Refract(const FVector2& incident, const FVector2& normal, float indexOfRefraction);
	static FVector2 BoundToRect(const FVector2& min, const FVector2& max, const FVector2& V);
	static FVector2 Clamp(const FVector2& V, float minLength, float maxLength);
	static FVector2 ClampValues(const FVector2& V, float minEntry, float maxEntry);
	static FVector2 ToUVCords(const FVector2& V);

	static float GetMax(const FVector2& V);
	static float GetMin(const FVector2& V);
	static FVector2 Abs(const FVector2& V);
	static FVector2 Reciprocal(const FVector2& V);
	static FVector2 GetSignVector(const FVector2& V);

	static std::string ToString(const FVector2& V, const int numDigits);

	// Add lots of others here

	static bool IsEqual(FVector2 a, FVector2 b);

	operator glm::vec2() const { return glm::vec2(this->x, this->y); }
	operator ImVec2() const { return ImVec2(this->x, this->y); }
	
	operator std::string() const { return ToString(*this, 5); }

	bool operator==(const FVector2 Other) const;

	FVector2 operator+(const FVector2 Other) const;
	FVector2 operator+=(const FVector2 Other);
	FVector2 operator-(const FVector2 Other) const;
	FVector2 operator-=(const FVector2 Other);
	FVector2 operator*(const float f) const;
	FVector2 operator*=(const float f);
	FVector2 operator/(const float f) const;
	FVector2 operator/=(const float f);

	static const FVector2 const left;
	static const FVector2 const right;
	static const FVector2 const down;
	static const FVector2 const up;
};

FVector2 operator*(float f, const FVector2& V);