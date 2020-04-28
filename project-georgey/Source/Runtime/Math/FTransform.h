#pragma once
#include "FVector3.h"
#include "FQuaternion.h"

struct FTransform
{
	FVector3 position;
	FQuaternion rotation;
	FVector3 scale;

	FTransform();
	FTransform(FVector3 position, FQuaternion rotation);
	FTransform(FVector3 position, FQuaternion rotation, FVector3 scale);
};