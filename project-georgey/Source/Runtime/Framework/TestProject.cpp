#include <string>
#include <vector>
#include "Project.h"
#include "Component.h"
#include "Params.h"

#include "../Rendering/MeshComponent.h"
#include "../Particles/ParticleSystem.h"
#include "../Rendering/Billboard.h"
#include "../UI/TextComponent.h"

std::string projectName = "Test Project";

unsigned short DefaultTagStringToNum(const char* string)
{
	if (strcmp(string, "Player"))
	{
		return 1;
	}
	if (strcmp(string, "Enemy"))
	{
		return 2;
	}
	return 0;
}

std::string DefaultTagNumToString(unsigned short num)
{
	switch (num)
	{
	case 1:
		return "Player";
	case 2:
		return "Enemy";
	}
	return "";
}

template <class T>
unsigned int DefaultClassTypeToInt()
{
	return 0;
}

template<> unsigned int DefaultClassTypeToInt<TestComponent>() { return 2; }

template<> unsigned int DefaultClassTypeToInt<MeshComponent>() { return 101; }
template<> unsigned int DefaultClassTypeToInt<ParticleSystem>() { return 102; }
template<> unsigned int DefaultClassTypeToInt<Billboard>() { return 103; }
template<> unsigned int DefaultClassTypeToInt<TextComponent>() { return 104; }

std::vector<std::string> GetParamsList(unsigned int classId)
{
	switch (classId)
	{
	case 2:
		return std::vector<std::string>();
	case 101:
		return std::vector<std::string>({"meshShader", "meshData", "isVisible"});
	case 102:
		return std::vector<std::string>();
	case 103:
		return std::vector<std::string>({"billboardTexture", "sizeType", "orientation", "billboardSize"});
	case 104:
		return std::vector<std::string>({"margins", "fontSize", "text", "font", "shader"});
	}
	return std::vector<std::string>();
}

template<class T>
void SetComponentParams(std::vector<std::string> params, T* component) { }

template<> void SetComponentParams(std::vector<std::string> params, MeshComponent* component)
{
	component->meshShader = ParseShader(params[0]);
	component->meshData = ParseMesh(params[1]);
	component->isVisible = ParseBool(params[2]);
}

template<> void SetComponentParams(std::vector<std::string> params, Billboard* component)
{
	component->billboardTexture = ParseTexture(params[0]);
	component->sizeType = (EBillboardSizeType)ParseInt(params[1]);
	component->orientation = (EBilboardOrientation)ParseInt(params[2]);
	component->billboardSize = ParseVector2(params[3]);
}

template<> void SetComponentParams(std::vector<std::string> params, TextComponent* component)
{
	component->margins = ParseFloat(params[0]);
	component->fontSize = ParseInt(params[1]);
	component->text = params[2];
	component->font = ParseFont(params[3]);
	component->shader = ParseShader(params[4]);
}

void AddComponentToScene(unsigned int classId, std::vector<std::string> params, GameObject* gameObject, uint8_t sceneId)
{
	switch (classId)
	{
	case 101: { PB_EMPLACE_COMPONENT(MeshComponent, classId); PB_START(); } break;
	case 102: { PB_EMPLACE_COMPONENT(ParticleSystem, classId); PB_START(); } break;
	case 103: { PB_EMPLACE_COMPONENT(Billboard, classId); PB_START(); } break;
	case 104: { PB_EMPLACE_COMPONENT(TextComponent, classId); PB_START(); } break;
	}
}