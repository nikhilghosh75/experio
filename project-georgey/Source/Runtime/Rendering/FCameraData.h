#pragma once
#include "../Math/FTransform.h"

struct FCameraData
{
	FTransform cameraTransform;
	float fieldOfView;
	float nearClipPlane = 0.1f;
	float farClipPlane = 100.f;

	FCameraData();
	FCameraData(float fieldOfView);
	FCameraData(FTransform cameraTransform, float fieldOfView);
	FCameraData(FVector3 position, FQuaternion rotation, float fieldOfView);
};