#include "DemoProjectEditor.h"
#include "Framework/SaveParams.h"
#include "BuildSystem\BinarySaveParams.h"

template<typename T>
void SaveComponentParams(T* component, std::ofstream& stream) {};

void SaveComponentToScene(unsigned int componentID, Component* component, std::ofstream& stream)
{
	switch (componentID)
	{
	case 100: PB_SAVE_COMPONENT(VirtualCamera); break;
	case 101: PB_SAVE_COMPONENT(MeshComponent); break;
	case 102: PB_SAVE_COMPONENT(ParticleSystem); break;
	case 103: PB_SAVE_COMPONENT(Billboard); break;
	}
}

void SaveComponentParams<VirtualCamera>(VirtualCamera* component, std::ofstream& stream)
{
	PB_SAVE_PARAM("priority", component->priority, SaveFloat);
	PB_SAVE_PARAM("fieldOfView", component->fieldOfView, SaveFloat);
	PB_SAVE_PARAM("nearClipPlane", component->nearClipPlane, SaveFloat);
	PB_SAVE_PARAM("farClipPlane", component->farClipPlane, SaveFloat);
}

void SaveComponentParams<MeshComponent>(MeshComponent* component, std::ofstream& stream)
{
	PB_SAVE_PARAM("material", component->material, SaveMaterial);
	PB_SAVE_PARAM("meshData", component->meshData, SaveMesh);
	PB_SAVE_PARAM("isVisible", component->isVisible, SaveBool);
}

void SaveComponentParams<ParticleSystem>(ParticleSystem* component, std::ofstream& stream)
{

}

void SaveComponentParams<Billboard>(Billboard* component, std::ofstream& stream)
{
	PB_SAVE_PARAM("billboardTexture", component->billboardTexture, SaveTexture);
	PB_SAVE_PARAM("sizeType", (uint8_t)component->sizeType, SaveByte);
	PB_SAVE_PARAM("orientation", (uint8_t)component->orientation, SaveByte);
	PB_SAVE_PARAM("billboardSize", component->billboardSize, SaveVector2);
}

template<typename T>
void SaveComponentBinaryParams(T* component, std::ofstream& stream) {};

void SaveBinaryComponentToScene(unsigned int componentID, Component* component, std::ofstream& stream)
{
	switch (componentID)
	{
	case 100: PB_SAVE_BINARY_COMPONENT(VirtualCamera); break;
	case 101: PB_SAVE_BINARY_COMPONENT(MeshComponent); break;
	case 102: PB_SAVE_BINARY_COMPONENT(ParticleSystem); break;
	case 103: PB_SAVE_BINARY_COMPONENT(Billboard); break;
	}
}

void SaveComponentBinaryParams<VirtualCamera>(VirtualCamera* component, std::ofstream& stream)
{
	BinarySaveFloat(component->priority, stream);
	BinarySaveFloat(component->fieldOfView, stream);
	BinarySaveFloat(component->nearClipPlane, stream);
	BinarySaveFloat(component->farClipPlane, stream);
}

void SaveComponentBinaryParams<MeshComponent>(MeshComponent* component, std::ofstream& stream)
{
	BinarySaveMaterial(component->material, stream);
	BinarySaveMesh(component->meshData, stream);
	BinarySaveBool(component->isVisible, stream);
}

void SaveComponentBinaryParams<ParticleSystem>(ParticleSystem* component, std::ofstream& stream)
{

}

void SaveComponentBinaryParams<Billboard>(Billboard* component, std::ofstream& stream)
{
	BinarySaveTexture(component->billboardTexture, stream);
	BinarySaveByte((uint8_t)component->sizeType, stream);
	BinarySaveByte((uint8_t)component->orientation, stream);
	BinarySaveVector2(component->billboardSize, stream);
}