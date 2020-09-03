#include "MeshComponent.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Files/Mesh/MeshReader.h"
#include "../Camera/CameraSystem.h"
#include "Renderer.h"

MeshComponent::MeshComponent()
{
	this->isVisible = true;
}

MeshComponent::MeshComponent(GameObject * object)
{
	this->isVisible = true;
	this->gameObject = object;
}

MeshComponent::MeshComponent(MeshData * newMeshData)
{
	this->isVisible = true;
	this->meshData = newMeshData;
}

glm::mat4 MeshComponent::GetModelMatrix() const
{
	return this->modelMatrix;
}

void MeshComponent::Start()
{
	if (this->meshData == nullptr)
	{
		this->meshData = MeshReader::ReadFile("C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Meshes/suzanne.obj");
	}
}

void MeshComponent::Update()
{
	// Replace Later
	RecalculateModelMatrix();

	Renderer::Get()->DrawMesh(*this, CameraSystem::currentViewMatrix, CameraSystem::currentProjectionMatrix);
}

void MeshComponent::RecalculateModelMatrix()
{
	FVector3 position = gameObject->GetPosition();
	FQuaternion rotation = gameObject->GetRotation();
	FVector3 scale = gameObject->GetScale();

	glm::mat4 translationMatrix = glm::translate((glm::vec3)position);
	glm::mat4 rotationMatrix = glm::toMat4((glm::quat)rotation);
	glm::mat4 scaleMatrix = glm::scale((glm::vec3)scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}
