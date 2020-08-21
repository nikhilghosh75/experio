#include "FVector4.h"

FVector4::FVector4()
{
	this->w = 0;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

FVector4::FVector4(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}
