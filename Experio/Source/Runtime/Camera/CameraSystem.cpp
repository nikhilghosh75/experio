#include "CameraSystem.h"
#include "../Math/LMath.h"
#include "../Debug/Debug.h"
#include "../Framework/Params.h"

float CameraSystem::timeInTransition = 0.f;
float CameraSystem::transitionTime = 1.5f;
std::vector<VirtualCamera> CameraSystem::cameras;
glm::mat4 CameraSystem::currentViewMatrix;
glm::mat4 CameraSystem::currentProjectionMatrix;
VirtualCamera* CameraSystem::currentCamera;

VirtualCamera* CameraSystem::AddComponent(GameObject* gameObject)
{
	VirtualCamera tempCamera(gameObject);
	tempCamera.priority = 0.0f;
	tempCamera.fieldOfView = 45.f;
	cameras.push_back(tempCamera);
	return &cameras[cameras.size() - 1];
}

VirtualCamera* CameraSystem::AddComponent(std::vector<std::string> params, GameObject* gameObject)
{
	VirtualCamera tempCamera(gameObject);
	tempCamera.priority = ParseFloat(params[0]);
	tempCamera.fieldOfView = ParseFloat(params[1]);
	tempCamera.nearClipPlane = ParseFloat(params[2]);
	tempCamera.farClipPlane = ParseFloat(params[3]);
	tempCamera.Start();
	cameras.push_back(tempCamera);
	return &cameras[cameras.size() - 1];
}

VirtualCamera* CameraSystem::GetComponent(GameObject* gameObject)
{
	for (int i = 0; i < cameras.size(); i++)
	{
		if (cameras[i].GetGameObject() == gameObject)
		{
			return &cameras[i];
		} 
	}
	return nullptr;
}

void CameraSystem::DeleteComponent(GameObject * gameObject)
{
	bool foundComponent = false;
	for (int i = 0; i < cameras.size(); i++)
	{
		if (gameObject == cameras[i].GetGameObject())
		{
			foundComponent = true;
		}
		if (foundComponent)
		{
			if (i + 1 == cameras.size())
			{
				cameras.pop_back();
				return;
			}
			cameras[i] = cameras[i + 1];
		}
	}
}

void CameraSystem::OnGameObjectDeleted(GameObject * gameObject)
{
	DeleteComponent(gameObject);
}

void CameraSystem::Update()
{
	if (cameras.size() == 0)
	{
		Debug::LogError("There are no cameras in the scene");
		return;
	}

	VirtualCamera* tempCurrentCamera = GetCurrentCamera();

	if (currentCamera == nullptr)
	{
		currentCamera = tempCurrentCamera;
		currentViewMatrix = currentCamera->GetViewMatrix();
		currentProjectionMatrix = currentCamera->GetProjectionMatrix();
	}
	else if (tempCurrentCamera != currentCamera)
	{
		if (timeInTransition < 0.001f)
		{
			timeInTransition = transitionTime;
			currentViewMatrix = currentCamera->GetViewMatrix();
			currentProjectionMatrix = currentCamera->GetProjectionMatrix();
		}
		else
		{
			timeInTransition -= GameTime::deltaTime;
			if (timeInTransition < 0.001f)
			{
				timeInTransition = 0.0000f;
				currentCamera = tempCurrentCamera;
			}

			currentViewMatrix = LerpCamerasViewMatrix(tempCurrentCamera, currentCamera, timeInTransition / transitionTime);
			currentProjectionMatrix = LerpCamerasProjectionMatrix(tempCurrentCamera, currentCamera, timeInTransition / transitionTime);
		}
	}
	else
	{
		currentViewMatrix = currentCamera->GetViewMatrix();
		currentProjectionMatrix = currentCamera->GetProjectionMatrix();
	}
}

unsigned int CameraSystem::Size()
{
	return cameras.size();
}

VirtualCamera * CameraSystem::GetCurrentCamera()
{
	int maxIndex = 0;
	for (int i = 1; i < cameras.size(); i++)
	{
		if (cameras[i].GetGameObject() == nullptr)
		{
			continue;
		}
		if (cameras[i].priority > cameras[maxIndex].priority)
		{
			maxIndex = i;
		}
	}
	
	return &cameras[maxIndex];
}

glm::mat4 CameraSystem::LerpCamerasViewMatrix(VirtualCamera * c1, VirtualCamera * c2, float t)
{
	FVector3 lerpedPosition = FVector3::Lerp(c1->GetGameObject()->GetPosition(), c2->GetGameObject()->GetPosition(), t);
	FQuaternion lerpedRotation = FQuaternion::Slerp(c1->GetGameObject()->GetRotation(), c2->GetGameObject()->GetRotation(), t);
	return VirtualCamera::CalculateViewMatrix(lerpedPosition, lerpedRotation);
}

glm::mat4 CameraSystem::LerpCamerasProjectionMatrix(VirtualCamera * c1, VirtualCamera * c2, float t)
{
	float lerpedFOV = LMath::Lerp(c1->fieldOfView, c2->fieldOfView, t);
	float lerpedNearClip = LMath::Lerp(c1->nearClipPlane, c2->nearClipPlane, t);
	float lerpedFarClip = LMath::Lerp(c1->farClipPlane, c2->farClipPlane, t);
	return VirtualCamera::CalculateProjectionMatrix(lerpedFOV, lerpedNearClip, lerpedFarClip);
}