#pragma once

#include <string>
#include "FVector3.h"
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/ext.hpp"

struct FQuaternion
{
	float x, y, z, w;

	FQuaternion();
	FQuaternion(float x, float y, float z, float w);
	FQuaternion(glm::mat4 mat);
	//FQuaternion(TMatrix<4, 4, float> mat);
	FQuaternion(FVector3 axis, float angleInRadians);

	// Operators
	FQuaternion operator+(const FQuaternion Q) const;
	FQuaternion operator+=(const FQuaternion Q);
	FQuaternion operator-(const FQuaternion Q) const;
	FQuaternion operator-=(const FQuaternion Q);

	static float Magnitude(const FQuaternion& Q);
	static float SqrMagnitude(const FQuaternion& Q);

	static std::string ToString(const FQuaternion& Q);
	static glm::quat ToGLMQuat(const FQuaternion& Q);
	//static mat4 ToMat4(const FQuaternion& Q);
	static glm::mat4 ToGLMMat4(const FQuaternion& Q);

	operator std::string() const { return ToString(*this); };
	operator glm::quat() const { return ToGLMQuat(*this); };
	operator glm::mat4() const { return ToGLMMat4(*this); }

	FQuaternion operator*(const float f) const;
	FQuaternion operator*(const FQuaternion& Q) const;
	FQuaternion operator*=(float f);
	FQuaternion operator*=(const FQuaternion& Q);
	FQuaternion operator/(const float f) const;
	FQuaternion operator/=(float f);

	static FQuaternion GetConjugate(const FQuaternion& Q);

	static bool Equals(const FQuaternion& Q1, const FQuaternion Q2, float tolerance = 0.000001f);
	static bool IsIdentity(const FQuaternion& Q, float tolerance = 0.000001f);
	static bool IsUnit(const FQuaternion& Q, float tolerance = 0.0000001f);

	static FQuaternion MakeFromEuler(const FVector3& Euler); // x - roll, y - pitch, z - yaw
	static FVector3 ToEuler(const FQuaternion& Q);
	static float GetAngle(const FQuaternion& Q);

	static float Dot(const FQuaternion& Q1, const FQuaternion& Q2);

	static float AngularDistance(const FQuaternion& Q1, const FQuaternion& Q2);
	static FQuaternion Lerp(const FQuaternion& Q1, const FQuaternion& Q2, float t);
	static FQuaternion BiLerp(const FQuaternion& Q00, const FQuaternion& Q10, const FQuaternion& Q01, const FQuaternion& Q11, float t1, float t2);
	static FQuaternion Slerp(const FQuaternion& Q1, const FQuaternion& Q2, float t);
	static FQuaternion FindBetweenNormals(const FVector3& N1, const FVector3& N2);

	static FQuaternion LookAt(const FVector3 eye, const FVector3 center, const FVector3 up);

	static FVector3 GetRotationAxis(const FQuaternion& Q);
	static FVector3 GetForwardVector(const FQuaternion& Q);
	static FVector3 GetBackwardVector(const FQuaternion& Q);
	static FVector3 GetLeftVector(const FQuaternion& Q);
	static FVector3 GetRightVector(const FQuaternion& Q);
	static FVector3 GetUpVector(const FQuaternion& Q);
	static FVector3 GetDownVector(const FQuaternion& Q);
};

FQuaternion operator*(float f, const FQuaternion& Q);