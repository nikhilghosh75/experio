#include "FQuaternion.h"
#include "LMath.h"
#include "../Debug/GDebug.h"

FQuaternion::FQuaternion()
{
	this->w = 1;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

FQuaternion::FQuaternion(float x, float y, float z, float w)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

FQuaternion::FQuaternion(glm::mat4 mat)
{
	this->w = LMath::Sqrt(1 + mat[0][0] + mat[1][1] + mat[2][2]) / 2;
	float w4 = this->w * 4;
	this->x = (mat[1][2] - mat[2][1]) / w4;
	this->y = (mat[2][0] - mat[0][2]) / w4;
	this->z = (mat[0][1] - mat[1][0]) / w4;
}

FQuaternion::FQuaternion(FVector3 axis, float angleInRadians)
{
	this->w = LMath::Cos(angleInRadians);
	float sinOfAngle = LMath::Sin(angleInRadians);
	this->x = sinOfAngle * axis.x;
	this->y = sinOfAngle * axis.y;
	this->z = sinOfAngle * axis.z;
}

FQuaternion FQuaternion::operator+(const FQuaternion Q) const
{
	return FQuaternion(this->x + Q.x, this->y + Q.y, this->z + Q.z, this->w + Q.w);
}

FQuaternion FQuaternion::operator+=(const FQuaternion Q)
{
	return *this + Q;
}

FQuaternion FQuaternion::operator-(const FQuaternion Q) const
{
	return FQuaternion(this->x - Q.x, this->y - Q.y, this->z - Q.z, this->w - Q.w);
}

FQuaternion FQuaternion::operator-=(const FQuaternion Q)
{
	return *this - Q;
}

float FQuaternion::Magnitude(const FQuaternion & Q)
{
	return LMath::Sqrt(Q.w * Q.w + Q.x * Q.x + Q.y * Q.y + Q.z * Q.z);
}

float FQuaternion::SqrMagnitude(const FQuaternion & Q)
{
	return Q.w * Q.w + Q.x * Q.x + Q.y * Q.y + Q.z * Q.z;
}

glm::quat FQuaternion::ToGLMQuat(const FQuaternion & Q)
{
	glm::quat tempQuat = *(glm::quat*)&Q;
	return tempQuat;
}

/*
mat4 FQuaternion::ToMat4(const FQuaternion & Q)
{
	if (!IsUnit(Q))
	{
		GDebug::LogWarning("Quaternion is not a Unit Quaternion. Translation to matrix will not work");
	}
	float x = Q.x;
	float y = Q.y;
	float z = Q.z;
	float w = Q.w;
	float elements[16] = {
		1 - (2 * y * y) - (2 * z * z), (2 * x * y) + (2 * z * w), (2 * x * z) - (2 * y * w), 0.f, // Column 0
		(2 * x * y) - (2 * z * w), 1 - (2 * x * x) - (2 * z * z), (2 * z * y) + (2 * x * w), 0.f, // Column 1
		(2 * z * x) + (2 * y * w), (2 * z * y) - (2 * x * w), 1 - (2 * x * x) - (2 * y * y), 0.f, // Column 2
		0.f, 0.f, 0.f, 1.f // Column 3
	};
	return mat4(elements);
}
*/

glm::mat4 FQuaternion::ToGLMMat4(const FQuaternion & Q)
{
	float x = Q.x;
	float y = Q.y;
	float z = Q.z;
	float w = Q.w;
	glm::vec4 col0 = glm::vec4(1 - (2 * y * y) - (2 * z * z), (2 * x * y) + (2 * z * w), (2 * x * z) - (2 * y * w), 0.f);
	glm::vec4 col1 = glm::vec4((2 * x * y) - (2 * z * w), 1 - (2 * x * x) - (2 * z * z), (2 * z * y) + (2 * x * w), 0.f);
	glm::vec4 col2 = glm::vec4((2 * z * x) + (2 * y * w), (2 * z * y) - (2 * x * w), 1 - (2 * x * x) - (2 * y * y), 0.f);
	glm::vec4 col3 = glm::vec4(0.f, 0.f, 0.f, 1.f);
	return glm::mat4(col0, col1, col2, col3);
}

FQuaternion FQuaternion::operator*(const float f) const
{
	return FQuaternion(this->x * f, this->y * f, this->z * f, this->w * f);
}

FQuaternion FQuaternion::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	this->w *= f;
	return *this * f;
}

FQuaternion FQuaternion::operator/(const float f) const
{
	return FQuaternion(this->x / f, this->y / f, this->z / f, this->w / f);
}

FQuaternion FQuaternion::operator/=(float f)
{
	this->x /= f;
	this->y /= f;
	this->z /= f;
	this->w /= f;
	return *this / f;
}

FQuaternion FQuaternion::GetConjugate(const FQuaternion & Q)
{
	return FQuaternion(-Q.x, -Q.y, -Q.z, Q.w);
}

bool FQuaternion::Equals(const FQuaternion & Q1, const FQuaternion Q2, float tolerance)
{
	return LMath::ApproxEquals(Q1.x, Q2.x, tolerance) && LMath::ApproxEquals(Q1.y, Q2.y, tolerance) && LMath::ApproxEquals(Q1.z, Q1.z, tolerance) && LMath::ApproxEquals(Q1.w, Q2.w, tolerance);
}

bool FQuaternion::IsIdentity(const FQuaternion & Q, float tolerance)
{
	return LMath::ApproxEquals(Q.x, 0, tolerance) && LMath::ApproxEquals(Q.y, 0, tolerance) && LMath::ApproxEquals(Q.z, 0, tolerance) && LMath::ApproxEquals(Q.w, 1.f, tolerance);
}

bool FQuaternion::IsUnit(const FQuaternion & Q, float tolerance)
{
	return LMath::ApproxEquals(SqrMagnitude(Q), 1.f);
}

FQuaternion FQuaternion::MakeFromEuler(const FVector3 & Euler)
{
	float roll = Euler.x;
	float pitch = Euler.y;
	float yaw = Euler.z;

	float cy = cos(yaw * 0.5);
	float sy = sin(yaw * 0.5);
	float cp = cos(pitch * 0.5);
	float sp = sin(pitch * 0.5);
	float cr = cos(roll * 0.5);
	float sr = sin(roll * 0.5);

	FQuaternion q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = sr * cp * cy - cr * sp * sy;
	q.y = cr * sp * cy + sr * cp * sy;
	q.z = cr * cp * sy - sr * sp * cy;

	return q;
}

FVector3 FQuaternion::ToEuler(const FQuaternion & Q)
{
	float sinrCosp = 2 * (Q.w * Q.x * Q.y * Q.z);
	float cosrCosp = 1 - 2 * (Q.x * Q.x + Q.y * Q.y);
	float roll = LMath::Atan2(sinrCosp, cosrCosp);

	float sinp = 2 * (Q.w * Q.y - Q.z * Q.x);
	float pitch = 0.f;
	if (LMath::Abs(sinp) >= 1)
	{
		pitch = LMath::CopySign(PI / 2, sinp);
	}
	else
	{
		pitch = LMath::Asin(sinp);
	}

	float sinyCosp = 2 * (Q.w * Q.z + Q.x * Q.y);
	float cosyCosp = 1 - 2 * (Q.y * Q.y + Q.z * Q.z);
	float yaw = LMath::Atan2(sinyCosp, cosyCosp);

	return FVector3(roll, pitch, yaw);
}

float FQuaternion::GetAngle(const FQuaternion & Q)
{
	return 2.f * LMath::Acos(Q.w);
}

float FQuaternion::Dot(const FQuaternion & Q1, const FQuaternion & Q2)
{
	return Q1.x * Q2.x + Q1.y * Q2.y + Q1.z * Q2.z + Q1.w * Q2.w;
}

float FQuaternion::AngularDistance(const FQuaternion & Q1, const FQuaternion & Q2)
{
	float innerProduct = Q1.x * Q2.x + Q1.y * Q2.y + Q1.z * Q2.z + Q1.w * Q2.w;
	return LMath::Acos((2 * innerProduct * innerProduct) - 1.f);
}

FQuaternion FQuaternion::Lerp(const FQuaternion & Q1, const FQuaternion & Q2, float t)
{
	return FQuaternion(
		LMath::Lerp(Q1.x, Q2.x, t),
		LMath::Lerp(Q1.y, Q2.y, t),
		LMath::Lerp(Q1.z, Q2.z, t),
		LMath::Lerp(Q1.w, Q2.w, t)
	);
}

FQuaternion FQuaternion::BiLerp(const FQuaternion & Q00, const FQuaternion & Q10, const FQuaternion & Q01, const FQuaternion & Q11, float t1, float t2)
{
	return FQuaternion::Lerp(
		FQuaternion::Slerp(Q00, Q10, t1),
		FQuaternion::Slerp(Q01, Q11, t1),
		t2
	);
}

FQuaternion FQuaternion::Slerp(const FQuaternion & Q1, const FQuaternion & Quat2, float t)
{
	FQuaternion Q2 = Quat2;

	float dot = Dot(Q1, Q2);

	if (dot < 0.0f)
	{
		Q2 = Q2 * -1.f;
		dot = dot * -1.f;
	}

	const float DOT_THRESHOLD = 0.9995f;

	if (dot > DOT_THRESHOLD)
	{
		FQuaternion result = Q1 + t * (Q2 - Q1);
		return result;
	}

	float theta0 = LMath::Acos(dot);
	float theta = theta0 * t;
	float sinTheta = LMath::Sin(theta);
	float sinTheta0 = LMath::Sin(theta0);

	float s0 = LMath::Cos(theta) - dot * sinTheta / sinTheta0;
	float s1 = sinTheta / sinTheta0;

	return (s0 * Q1) + (s1 * Q2);
}

FQuaternion operator*(float f, const FQuaternion & Q)
{
	return FQuaternion(Q.x * f, Q.y * f, Q.z * f, Q.w * f);
}
