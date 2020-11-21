#pragma once

#include "imgui.h"
#include <string>

struct FVector4
{
	float w;
	float x;
	float y;
	float z;

	FVector4();
	FVector4(float w, float x, float y, float z);
	FVector4(ImVec4 V);

	float Magnitude();
	float SqrMagnitude();

	static float Magnitude(const FVector4& V);
	static float SqrMagnitude(const FVector4& V);

	float Distance(const FVector4& V);
	float SqrDistance(const FVector4& V);

	static float Distance(const FVector4& V1, const FVector4 V2);
	static float SqrDistance(const FVector4& V1, const FVector4 V2);

	static float Dot(const FVector4& V1, const FVector4 V2);

	static FVector4 Abs(const FVector4& V);
	static FVector4 Reflect(const FVector4& Incident, const FVector4& Normal);
	static FVector4 Refract(const FVector4& Incident, const FVector4& Normal, float indexOfRefraction);
	static FVector4 BoundToTesseract(const FVector4& V, const FVector4& Min, const FVector4& Max);

	FVector4 operator+(const FVector4& V) const;
	FVector4 operator+=(const FVector4& V);
	FVector4 operator-(const FVector4& V) const;
	FVector4 operator-=(const FVector4& V);
	FVector4 operator*(const float f) const;
	FVector4 operator*=(const float f);
	FVector4 operator/(const float f) const;
	FVector4 operator/=(const float f);

	operator ImVec4() const { return ImVec4(this->x, this->y, this->z, this->w); }

	operator std::string() const;
};

FVector4 operator*(float f, const FVector4& V);