#include "AdditionalCameras.h"
#include "VirtualCamera.h"
#include "../Math/LMath.h"

glm::mat4 AdditionalCameras::viewMatrix;
glm::mat4 AdditionalCameras::projectionMatrix;

void AdditionalCameras::CalculateViewMatrix(glm::vec3 position, glm::quat rotation)
{
	viewMatrix = VirtualCamera::CalculateViewMatrix(position, rotation);
}

void AdditionalCameras::CalculateViewMatrix(FVector3 position, FQuaternion rotation)
{
	viewMatrix = VirtualCamera::CalculateViewMatrix(position, rotation);
}

void AdditionalCameras::CalculateProjectionMatrix(float fieldOfView, float nearClipPlane, float farClipPlane, float aspectRatio)
{
	projectionMatrix = glm::perspective(
		LMath::DegreesToRadians(fieldOfView),
		aspectRatio,
		nearClipPlane,
		farClipPlane
	);
}
