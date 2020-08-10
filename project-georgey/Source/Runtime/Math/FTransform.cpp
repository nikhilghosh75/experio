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

FTransform::FTransform(float posX, float posY, float posZ, float quatX, float quatY, float quatZ, float quatW, float scaleX, float scaleY, float scaleZ)
{
	this->position = FVector3(posX, posY, posY);
	this->rotation = FQuaternion(quatX, quatY, quatZ, quatW);
	this->scale = FVector3(scaleX, scaleY, scaleZ);
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

void FTransform::Translate(FVector3 translationAmount)
{
	this->position += translationAmount;
}

void FTransform::Rotate(FQuaternion rotation)
{
	this->rotation = rotation;
}

void FTransform::Scale(float scale)
{
	this->scale *= scale;
}
