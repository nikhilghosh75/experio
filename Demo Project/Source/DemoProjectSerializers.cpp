#include "DemoProject.h"
#include "Runtime/Framework/BinaryParams.h"
#include "Runtime/Framework/SceneLoader.h"

std::vector<std::string> GetParamsList(unsigned int classId)
{
	switch(classId)
	{
		case 104: return std::vector<std::string>({ "margins", "fontSize", "text", "font", "shader"});
		case 1024: return std::vector<std::string>({ "isActive = false", "isAccelerating = false", "acceleration", "topSpeed"});
		case 100: return std::vector<std::string>({ "priority", "fieldOfView", "nearClipPlane", "farClipPlane"});
		case 101: return std::vector<std::string>({ "material", "meshData", "isVisible"});
		case 102: return std::vector<std::string>({ });
		case 103: return std::vector<std::string>({ "billboardTexture", "sizeType", "orientation", "billboardSize"});
	}
	return std::vector<std::string>();
}

template<class T> void SetComponentParams(std::vector<std::string> params, T* component) { }

template<> void SetComponentParams(std::vector<std::string> params, TextComponent* component)
{
	component->margins = ParseFloat(params[0]);
	component->fontSize = ParseInt(params[1]);
	component->font = ParseFont(params[2]);
	component->shader = ParseShader(params[3]);
}

template<> void SetComponentParams(std::vector<std::string> params, Spaceship* component)
{
	component->acceleration = ParseFloat(params[0]);
	component->topSpeed = ParseFloat(params[1]);
}

template<> void SetComponentParams(std::vector<std::string> params, VirtualCamera* component)
{
	component->priority = ParseFloat(params[0]);
	component->fieldOfView = ParseFloat(params[1]);
	component->nearClipPlane = ParseFloat(params[2]);
	component->farClipPlane = ParseFloat(params[3]);
}

template<> void SetComponentParams(std::vector<std::string> params, MeshComponent* component)
{
	component->material = (MeshMaterial*)ParseMaterial(params[0]);
	component->meshData = ParseMesh(params[1]);
	component->isVisible = ParseBool(params[2]);
}

template<> void SetComponentParams(std::vector<std::string> params, ParticleComponent* component)
{
}

template<> void SetComponentParams(std::vector<std::string> params, Billboard* component)
{
	component->billboardTexture = ParseTexture(params[0]);
	component->sizeType = (EBillboardSizeType)ParseUByte(params[1]);
	component->orientation = (EBilboardOrientation)ParseUByte(params[2]);
	component->billboardSize = ParseVector2(params[3]);
}

template<class T> void SetComponentBinaryParams(void* data, T* component) { }

template<> void SetComponentBinaryParams(void* data, TextComponent* component)
{
	component->margins = BinaryParseFloat((void*)((char*)data + 0));
	component->fontSize = BinaryParseInt((void*)((char*)data + 4));
	component->font = BinaryParseFont((void*)((char*)data + 8));
	component->shader = BinaryParseShader((void*)((char*)data + 12));
}

template<> void SetComponentBinaryParams(void* data, Spaceship* component)
{
	component->acceleration = BinaryParseFloat((void*)((char*)data + 0));
	component->topSpeed = BinaryParseFloat((void*)((char*)data + 4));
}

template<> void SetComponentBinaryParams(void* data, VirtualCamera* component)
{
	component->priority = BinaryParseFloat((void*)((char*)data + 0));
	component->fieldOfView = BinaryParseFloat((void*)((char*)data + 4));
	component->nearClipPlane = BinaryParseFloat((void*)((char*)data + 8));
	component->farClipPlane = BinaryParseFloat((void*)((char*)data + 12));
}

template<> void SetComponentBinaryParams(void* data, MeshComponent* component)
{
	component->material = (MeshMaterial*)BinaryParseMaterial((void*)((char*)data + 0));
	component->meshData = BinaryParseMesh((void*)((char*)data + 4));
	component->isVisible = BinaryParseBool((void*)((char*)data + 8));
}

template<> void SetComponentBinaryParams(void* data, ParticleComponent* component)
{
}

template<> void SetComponentBinaryParams(void* data, Billboard* component)
{
	component->billboardTexture = BinaryParseTexture((void*)((char*)data + 0));
	component->sizeType = (EBillboardSizeType)BinaryParseUByte((void*)((char*)data + 4));
	component->orientation = (EBilboardOrientation)BinaryParseUByte((void*)((char*)data + 5));
	component->billboardSize = BinaryParseVector2((void*)((char*)data + 6));
}

void AddComponentToScene(unsigned int classId, std::vector<std::string> params, GameObject* gameObject, uint8_t sceneId)
{
	switch(classId)
	{
		case 104: { PB_EMPLACE_COMPONENT(TextComponent, classId); PB_START_COMPONENT(); } break;
		case 1024: { PB_EMPLACE_COMPONENT(Spaceship, classId); PB_START_COMPONENT(); } break;
		case 100: { PB_EMPLACE_COMPONENT(VirtualCamera, classId); PB_START_COMPONENT(); } break;
		case 101: { PB_EMPLACE_COMPONENT(MeshComponent, classId); PB_START_COMPONENT(); } break;
		case 102: { PB_EMPLACE_COMPONENT(ParticleComponent, classId); PB_START_COMPONENT(); } break;
		case 103: { PB_EMPLACE_COMPONENT(Billboard, classId); PB_START_COMPONENT(); } break;
	}
}

void AddComponentToScene(unsigned int classId, void* params, size_t paramSize, GameObject* gameObject, uint8_t sceneId)
{
	switch(classId)
	{
		case 104: { PB_EMPLACE_BINARY_COMPONENT(TextComponent, classId); PB_START_COMPONENT(); } break;
		case 1024: { PB_EMPLACE_BINARY_COMPONENT(Spaceship, classId); PB_START_COMPONENT(); } break;
		case 100: { PB_EMPLACE_BINARY_COMPONENT(VirtualCamera, classId); PB_START_COMPONENT(); } break;
		case 101: { PB_EMPLACE_BINARY_COMPONENT(MeshComponent, classId); PB_START_COMPONENT(); } break;
		case 102: { PB_EMPLACE_BINARY_COMPONENT(ParticleComponent, classId); PB_START_COMPONENT(); } break;
		case 103: { PB_EMPLACE_BINARY_COMPONENT(Billboard, classId); PB_START_COMPONENT(); } break;
	}
}

size_t SizeOfComponent(unsigned int classId)
{
	switch(classId)
	{
		case 104: return sizeof(TextComponent);
		case 1024: return sizeof(Spaceship);
		case 100: return sizeof(VirtualCamera);
		case 101: return sizeof(MeshComponent);
		case 102: return sizeof(ParticleComponent);
		case 103: return sizeof(Billboard);
	}
	return 0;
}

size_t SerializedSizeOfComponent(unsigned int classId)
{
	switch(classId)
	{
		case 104: return 16;
		case 1024: return 8;
		case 100: return 16;
		case 101: return 9;
		case 102: return 0;
		case 103: return 14;
	}
	return 0;
}

