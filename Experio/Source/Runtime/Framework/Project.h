#pragma once
#include <string>
#include "ComponentManager.h"
#include "../Rendering/Materials/MaterialManager.h"

class Project
{
public:
	static bool inEditor;

	static bool projectRunning;

	static std::string projectName;

	static ComponentManager* componentManager;

	static MaterialManager* materialManager;

	static void BeginFrame();
	static void EndFrame();

	static void StartGame();

	static void EndGame();

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

#define PB_EMPLACE_BINARY_COMPONENT(_className_, _classID_) \
	_className_* component = (_className_*)Project::componentManager->AddComponent(gameObject, _classID_);\
	SetComponentBinaryParams<_className_>(params, component);

#define PB_SAVE_COMPONENT(_className_) SaveComponentParams<_className_>((_className_*)component, stream);

#define PB_SAVE_BINARY_COMPONENT(_className_) SaveComponentBinaryParams((_className_*)component, stream);

#define PB_SAVE_PARAM(_paramName_, _param_, _saveFunction_) stream << "\t\t\t" << _paramName_ << ": "; \
	_saveFunction_(_param_, stream); \
	stream << std::endl;

#define PB_START_COMPONENT() component->Start();