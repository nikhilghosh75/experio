#include "VirtualCamera.h"
#include "CameraSystem.h"
#include "../Core/Window.h"
#include "../Core/LWindowOperations.h"
#include "../Math/LMath.h"
#include "../Math/FRay.h"

VirtualCamera::VirtualCamera(GameObject * object)
{
	this->gameObject = object;
}

glm::mat4 VirtualCamera::GetViewMatrix() const
{
	return (glm::mat4)this->gameObject->GetRotation() * glm::translate(glm::mat4(), (glm::vec3)(this->gameObject->GetPosition() * -1.f ));
}

glm::mat4 VirtualCamera::GetProjectionMatrix() const
{
	float aspectRatio = LWindowOperations::GetAspectRatio(Window::GetWindowData());
	return glm::perspective(
		LMath::DegreesToRadians(this->fieldOfView), 
		aspectRatio, 
		this->nearClipPlane, 
		this->farClipPlane
	);
}

glm::mat4 VirtualCamera::CalculateViewMatrix(glm::vec3 position, glm::quat rotation)
{
	return (glm::mat4)rotation * glm::translate(glm::mat4(), position * -1.f);
}

glm::mat4 VirtualCamera::CalculateProjectionMatrix(float fieldOfView, float nearClipPlane, float farClipPlane)
{
	float aspectRatio = LWindowOperations::GetAspectRatio(Window::Get()->GetWindowData());
	return glm::perspective(
		LMath::DegreesToRadians(fieldOfView),
		aspectRatio,
		nearClipPlane,
		farClipPlane
	);
}

FRay VirtualCamera::ScreenPointToRay(float x, float y)
{
	return ScreenPointToRay(FVector2(x, y));
}

FRay VirtualCamera::ScreenPointToRay(FVector2 point)
{
	glm::mat4 VP = GetProjectionMatrix() * GetViewMatrix();
	glm::mat4 VPInv = glm::inverse(VP);
	FWindowData data = Window::GetWindowData();
	FVector2 clippedPoint = LWindowOperations::PixelToClippedPos(data, point);
	glm::vec4 mousePoint = glm::vec4(clippedPoint.x, clippedPoint.y, -0.25, 1.0);
	glm::vec4 worldPosition = VPInv * mousePoint;

	worldPosition.w = 1.0 / worldPosition.w;
	worldPosition.x *= worldPosition.w;
	worldPosition.y *= worldPosition.w;
	worldPosition.z *= worldPosition.w;

	return FRay::BetweenPoints(gameObject->GetPosition(), (FVector3)(glm::vec3)worldPosition);
}
