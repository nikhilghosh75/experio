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

MeshComponent::MeshComponent(MeshData * newMeshData, Shader * newShader)
{
	this->isVisible = true;
	this->meshData = newMeshData;
	this->meshShader = newShader;
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

	if (this->meshShader == nullptr)
	{
		this->meshShader = new Shader(
			"C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/BasicVertex.shader", 
			"C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/BasicFragment.shader"
		);
	}
}

void MeshComponent::Update()
{
	// Replace Later
	this->meshShader->Bind();

	glm::vec3 lightPosition = glm::vec3(4, 4, 4);
	this->meshShader->SetUniformVec3("LightWorldPosition", lightPosition);

	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	this->meshShader->SetUniformVec3("LightColor", lightColor);

	float lightIntensity = 50.0f;
	this->meshShader->SetUniformFloat("LightPower", lightIntensity);

	Texture albedoTexture("C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Textures/uvmap.bmp");
	albedoTexture.Bind(0);
	this->meshShader->SetUniformInt("albedoTexture", 0);

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
