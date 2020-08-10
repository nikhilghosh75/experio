#include "MeshComponent.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Files/Mesh/OBJReader.h"
#include "../Camera/FCameraData.h"
#include "Renderer.h"

MeshComponent::MeshComponent()
{
	this->isVisible = true;
	Start();
}

MeshComponent::MeshComponent(GameObject * object)
{
	this->gameObject = object;
	Start();
}

MeshComponent::MeshComponent(MeshData * newMeshData, Shader * newShader)
{
	this->isVisible = true;
	this->meshData = newMeshData;
	this->meshShader = newShader;
}

void MeshComponent::SetTransform(FTransform newTransform)
{
	this->transform = newTransform;
	//this->transform.OnTransformChange.AddListener(this->*(MeshComponent::RecalculateModelMatrix));
	RecalculateModelMatrix();
}

glm::mat4 MeshComponent::GetModelMatrix() const
{
	return this->modelMatrix;
}

void MeshComponent::Start()
{
	this->isVisible = true;
	if (this->meshData == nullptr)
	{
		OBJReader reader;
		this->meshData = reader.ReadFile("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Meshes/suzanne.obj");
	}

	if (this->meshShader == nullptr)
	{
		this->meshShader = new Shader(
			"C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", 
			"C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader"
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

	Texture albedoTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/uvmap.bmp");
	albedoTexture.Bind(0);
	this->meshShader->SetUniformInt("albedoTexture", 0);

	RecalculateModelMatrix();

	FCameraData camera(FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), 45.f);

	Renderer::Get()->DrawMesh(*this, camera);
}

void MeshComponent::RecalculateModelMatrix()
{
	FVector3 position = gameObject->transform.GetPosition();
	FQuaternion rotation = gameObject->transform.GetRotation();
	FVector3 scale = gameObject->transform.GetScale();

	glm::mat4 translationMatrix = glm::translate((glm::vec3)position);
	glm::mat4 rotationMatrix = glm::toMat4((glm::quat)rotation);
	glm::mat4 scaleMatrix = glm::scale((glm::vec3)scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}
