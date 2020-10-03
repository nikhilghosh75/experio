#pragma once
#include <string>
#include "ComponentManager.h"
#include "../Rendering/Materials/MaterialManager.h"

class Project
{
public:
	static bool inEditor;

	static std::string projectName;

	static ComponentManager* componentManager;

	static MaterialManager* materialManager;

	static void BeginFrame();
	static void EndFrame();

	static void StartGame();

	static unsigned short TagStringToNum(const char* string);

	static std::string TagNumToString(unsigned short num);

	template<class T>
	static unsigned int ClassTypeToInt();

	template<class T>
	static std::string ClassTypeToString();
};

#define PB_EMPLACE_COMPONENT(_className_, _classID_) \
	_className_* component = (_className_*)Project::componentManager->AddComponent(gameObject, _classID_);\
	SetComponentParams<_className_>(params, component);

#define PB_START() component->Start();