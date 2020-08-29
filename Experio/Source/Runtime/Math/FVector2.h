#pragma once
#include "FVector3.h"

#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/glm.hpp"

struct FVector2
{
	float x;
	float y;

	FVector2();
	FVector2(float x, float y);
	//FVector2(FVector3 V);

	float Magnitude() const;
	float SqrMagnitude() const;

	float Distance(const FVector2& V) const;
	float SqrDistance(const FVector2& V) const;

	static float Distance(const FVector2& V1, const FVector2& V2);
	static float SqrDistance(const FVector2& V1, const FVector2& V2);

	FVector2 Normalized() const;
	FVector2 UVCords() const;

	static float Dot(const FVector2& V1, const FVector2& V2);
	static float Cross(const FVector2& V1, const FVector2& V2);
	static FVector2 Reflect(const FVector2& incident, const FVector2& normal);
	static FVector2 Refract(const FVector2& incident, const FVector2& normal, float indexOfRefraction);
	static FVector2 BoundToRect(const FVector2& min, const FVector2& max, const FVector2& V);
	static FVector2 Clamp(const FVector2& V, float minLength, float maxLength);
	static FVector2 ClampValues(const FVector2& V, float minEntry, float maxEntry);
	static FVector2 ToUVCords(const FVector2& V);

	// Add lots of others here

	static bool IsEqual(FVector2 a, FVector2 b);

	operator glm::vec2() const { return glm::vec2(this->x, this->y); }

	bool operator==(const FVector2 Other) const;

	FVector2 operator+(const FVector2 Other) const;
	FVector2 operator+=(const FVector2 Other);
	FVector2 operator-(const FVector2 Other) const;
	FVector2 operator-=(const FVector2 Other);
	FVector2 operator*(const float f) const;
	FVector2 operator*=(const float f);
	FVector2 operator/(const float f) const;
	FVector2 operator/=(const float f);
};

FVector2 operator*(float f, const FVector2& V);