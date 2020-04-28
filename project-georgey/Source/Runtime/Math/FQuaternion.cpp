#include "FQuaternion.h"
#include "LMath.h"

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

glm::quat FQuaternion::ToGLMQuat(const FQuaternion & Q)
{
	glm::quat tempQuat = *(glm::quat*)&Q;
	return tempQuat;
}
