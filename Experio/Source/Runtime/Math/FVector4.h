#pragma once

struct FVector4
{
	float w;
	float x;
	float y;
	float z;

	FVector4();
	FVector4(float w, float x, float y, float z);

	static float Magnitude(const FVector4& V);
	static float SqrMagnitude(const FVector4& V);

	static float Distance(const FVector4& V);
	static float SqrDistance(const FVector4& V);

	static float Dot(const FVector4& V);

	FVector4 operator+(const FVector4& V) const;
	FVector4 operator+=(const FVector4& V);
	FVector4 operator-(const FVector4& V);
	FVector4 operator-=(const FVector4& V);
	FVector4 operator*(const FVector4& V);
	FVector4 operator*=(const FVector4& V);
	FVector4 operator/(const FVector4& V);
	FVector4 operator/=(const FVector4& V);
};