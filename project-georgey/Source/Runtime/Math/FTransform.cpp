#include "FTransform.h"

FTransform::FTransform()
{
	this->position = FVector3(0, 0, 0);
	this->rotation = FQuaternion();
}
