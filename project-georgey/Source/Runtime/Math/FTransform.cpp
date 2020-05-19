#include "FTransform.h"

FTransform::FTransform()
{
	this->position = FVector3(0, 0, 0);
	this->rotation = FQuaternion();
	this->scale = FVector3(1, 1, 1);
}

FTransform::FTransform(FVector3 position, FQuaternion rotation)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = FVector3(1, 1, 1);
}

FTransform::FTransform(FVector3 position, FQuaternion rotation, FVector3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void FTransform::SetPosition(FVector3 position)
{
	this->position = position;
}

void FTransform::SetRotation(FQuaternion rotation)
{
	this->rotation = rotation;
}

void FTransform::SetScale(FVector3 scale)
{
	this->scale = scale;
}
