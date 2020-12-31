#pragma once

#include <string>
#include "CreateMenu.h"
#include "../CodeParser/CodeProject.h"

class CreateSystem
{
public:
	static void CreateCppClass(const std::string& filepath, ECodeClassBase classType, const std::string& className = "NewClass");

	static void CreateDatatable(const std::string& filepath);

	static void CreateScene(const std::string& filepath);

	static void CreateText(const std::string& filepath);

private:
	static void CreateEmptyClass(const std::string& filepath, const std::string& className, ECodingLanguage langauge);

	static void CreateComponentClass(const std::string& filepath, const std::string& className, ECodingLanguage langauge);

	static void CreateSystemClass(const std::string& filepath, const std::string& className, ECodingLanguage langauge);

	static void CreateLibraryClass(const std::string& filepath, const std::string& className, ECodingLanguage langauge);
};