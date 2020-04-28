#pragma once
#include "../Math/FTransform.h"

struct FCameraData
{
	FTransform cameraTransform;
	float fieldOfView;
	FVector3 upVector;

	FCameraData();
	FCameraData(float fieldOfView);
	FCameraData(FTransform cameraTransform, float fieldOfView);
	FCameraData(FVector3 position, FQuaternion rotation, float fieldOfView);
};