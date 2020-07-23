#pragma once
#include <string>
#include "ComponentManager.h"

class Project
{
public:
	static std::string projectName;

	static ComponentManager* componentManager;

	static unsigned short TagStringToNum(const char* string);

	static std::string TagNumToString(unsigned short num);

	template<class T>
	static unsigned int ClassTypeToInt();

	template<class T>
	static std::string ClassTypeToString();
};
