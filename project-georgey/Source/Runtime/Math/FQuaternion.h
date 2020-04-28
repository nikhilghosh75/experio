#pragma once

#include <string>
#include "TMatrix.h"
#include "FVector3.h"
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/ext.hpp"

struct FQuaternion
{
	float x, y, z, w;

	FQuaternion();
	FQuaternion(float x, float y, float z, float w);
	FQuaternion(TMatrix<4, 4, float> mat);
	FQuaternion(FVector3 axis, float angleInRadians);

	// Operators
	FQuaternion operator+(const FQuaternion Q) const;
	FQuaternion operator+=(const FQuaternion Q);
	FQuaternion operator-(const FQuaternion Q) const;
	FQuaternion operator-=(const FQuaternion Q);

	static std::string ToString(const FQuaternion& Q);
	static glm::quat ToGLMQuat(const FQuaternion& Q);

	operator string() const { return ToString(*this); };
	operator glm::quat() const { return ToGLMQuat(*this); };

	static bool Equals(const FQuaternion Q1, const FQuaternion Q2, float tolerance = 0.000001f);
	static bool IsIdentity(const FQuaternion Q, float tolerance = 0.000001f);

	static FQuaternion MakeFromEuler(const FVector3& Euler);
	static FVector3 ToEuler(const FQuaternion& Q);
	static float GetAngle(const FQuaternion& Q);

	static float AngularDistance(const FQuaternion& Q1, const FQuaternion& Q2);
	static FQuaternion Lerp(const FQuaternion& Q1, const FQuaternion& Q2, float t);
	static FQuaternion BiLerp(const FQuaternion& Q00, const FQuaternion& Q10, const FQuaternion& Q01, const FQuaternion& Q11, float t1, float t2);
	static FQuaternion Slerp(const FQuaternion& Q1, const FQuaternion& Q2, float t);
	static FQuaternion FindBetweenNormals(const FVector3& N1, const FVector3& N2);
	static FVector3 GetRotationAxis(const FQuaternion& Q);
};