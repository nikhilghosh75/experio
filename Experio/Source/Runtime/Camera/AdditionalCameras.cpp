#include "AdditionalCameras.h"
#include "VirtualCamera.h"
#include "../Math/LMath.h"
#include "../Math/FRay.h"
#include "../Core/Window.h"
#include "../Core/LWindowOperations.h"

glm::mat4 AdditionalCameras::viewMatrix;
glm::mat4 AdditionalCameras::projectionMatrix;
glm::vec3 AdditionalCameras::cameraPosition;

void AdditionalCameras::CalculateViewMatrix(glm::vec3 position, glm::quat rotation)
{
	cameraPosition = position;
	viewMatrix = VirtualCamera::CalculateViewMatrix(position, rotation);
}

void AdditionalCameras::CalculateViewMatrix(FVector3 position, FQuaternion rotation)
{
	cameraPosition = position;
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

FRay AdditionalCameras::ScreenPointToRay(FVector2 point)
{
	glm::mat4 VP = projectionMatrix * viewMatrix;
	glm::mat4 VPInv = glm::inverse(VP);
	FWindowData data = Window::GetWindowData();
	FVector2 clippedPoint = LWindowOperations::PixelToClippedPos(data, point);
	glm::vec4 mousePoint = glm::vec4(clippedPoint.x, clippedPoint.y, -0.25, 1.0);
	glm::vec4 worldPosition = VPInv * mousePoint;

	worldPosition.w = 1.0 / worldPosition.w;
	worldPosition.x *= worldPosition.w;
	worldPosition.y *= worldPosition.w;
	worldPosition.z *= worldPosition.w;

	return FRay::BetweenPoints(cameraPosition, (FVector3)(glm::vec3)worldPosition);
}
