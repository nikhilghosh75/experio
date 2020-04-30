#include "FQuaternion.h"
#include "LMath.h"
#include "../Debug/GDebug.h"

FQuaternion::FQuaternion()
{
	this->w = 0;
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

FQuaternion FQuaternion::GetConjugate(const FQuaternion & Q)
{
	return FQuaternion(-Q.x, -Q.y, -Q.z, Q.w);
}

bool FQuaternion::IsUnit(const FQuaternion & Q, float tolerance)
{
	return LMath::ApproxEquals(SqrMagnitude(Q), 1.f);
}
