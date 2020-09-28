#pragma once
#include <string>
#include "Runtime/Containers/THashtable.h"

class EditorProject
{
public:
	static THashtable<unsigned int, std::string> classes;

	static void TempSetup();
};

unsigned int DefaultClassStringToInt(std::string name);