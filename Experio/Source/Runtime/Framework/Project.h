#pragma once
#include <string>
#include "ComponentManager.h"
#include "../Rendering/Materials/MaterialManager.h"

/// <summary>
/// A class representing a Project, including the component and material manager
/// </summary>

template <class T>
extern unsigned int DefaultClassTypeToInt();

class Project
{
public:
	static bool inEditor;

	static bool projectRunning;

	static std::string projectName;

	static std::string projectAssetsPath;
	static std::string experioResourcesPath;

	static ComponentManager* componentManager;

	static MaterialManager* materialManager;

	static void BeginFrame();
	static void EndFrame();

	static void StartGame();

	static void EndGame();

	static unsigned short TagStringToNum(const char* string);

	static std::string TagNumToString(unsigned short num);

	template<class T>
	static unsigned int ClassTypeToInt()
	{
#ifdef EXPERIO_EDITOR
		return DefaultClassStringToInt(NAMEOF_TYPE(T));
#else
		return DefaultClassTypeToInt<T>();
#endif // EXPERIO_EDITOR
	}

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