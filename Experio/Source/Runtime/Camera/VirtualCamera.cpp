#include "VirtualCamera.h"
#include "CameraSystem.h"
#include "../Core/Window.h"
#include "../Core/LWindowOperations.h"
#include "../Math/LMath.h"

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
