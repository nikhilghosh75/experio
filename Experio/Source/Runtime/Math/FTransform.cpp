#include "FTransform.h"
#include "LMath.h"

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

bool FTransform::operator==(const FTransform & T) const
{
	return LMath::ApproxEquals(this->position.x, T.position.x) && LMath::ApproxEquals(this->position.y, T.position.y)
		&& LMath::ApproxEquals(this->position.z, T.position.z) && LMath::ApproxEquals(this->rotation.w, T.rotation.w)
		&& LMath::ApproxEquals(this->rotation.x, T.rotation.x) && LMath::ApproxEquals(this->rotation.y, T.rotation.y)
		&& LMath::ApproxEquals(this->rotation.z, T.rotation.z) && LMath::ApproxEquals(this->scale.x, T.scale.x)
		&& LMath::ApproxEquals(this->scale.y, T.scale.y) && LMath::ApproxEquals(this->scale.z, T.scale.z);
}
