#include "CppMetasystem.h"
#include "Runtime/Files/LFileOperations.h"
#include "ThirdParty/Magic Enum/magic_enum.hpp"
#include "../EditorProject.h"
#include "../../CodeParser/CodeProjectGenerator.h"
#include "../../CodeParser/LCodeParser.h"
#include <fstream>

void CppMetasystem::GenerateMetadata(const std::string& filepath, std::ofstream& outFile)
{
	ECodeClassBase classBase = GetCodeClassBase(filepath);
	outFile << "ClassType: " << magic_enum::enum_name(classBase) << std::endl;

	switch (classBase)
	{
	case ECodeClassBase::Component: GenerateComponentMetadata(filepath, outFile); break;
	case ECodeClassBase::Library: GenerateLibraryMetadata(filepath, outFile); break;
	}
}

ECodeClassBase CppMetasystem::GetCodeClassBase(const std::string& filepath)
{
	std::ifstream inFile(filepath);
	FileBuffer buffer = LFileOperations::ReadTrimmedFileToBuffer(inFile);

	if (buffer.Find("EXPERIO_LIBRARY") != std::string::npos)
		return ECodeClassBase::Library;

	if (buffer.Find("SETUP_COMPONENT(") != std::string::npos || buffer.Find("public Component") != std::string::npos)
		return ECodeClassBase::Component;

	return ECodeClassBase::None;
}

void CppMetasystem::GenerateComponentMetadata(const std::string& filepath, std::ofstream& outFile)
{
	std::string hFilepath = LFileOperations::ReplaceExtension(filepath, "h");

	CodeProject project;
	CodeProjectGenerator projectGenerator(hFilepath, &project);
	projectGenerator.GenerateFullProject();

	if (project.IsEmpty() || project.classes.size() == 0)
		return;

	std::string componentName = "";
	size_t componentIndex = 0;
	for (size_t i = 0; i < project.classes.size(); i++)
	{
		if (LCodeParser::InheritsFrom(project.classes[i], "Component"))
		{
			componentIndex = i;
			componentName = project.classes[i].name;
			break;
		}
	}

	outFile << "ComponentName: " << componentName << std::endl;

	unsigned int componentID = EditorProject::GetNextComponentIndex();
	outFile << "ComponentID: " << componentID << std::endl;

	// TO-DO: Add System Support for metadata files
	outFile << "Standalone: " << "true" << std::endl;

	outFile << "Category: " << GetComponentCategory(filepath) << std::endl;

	// TO-DO: Add support for custom stage
	outFile << "Stage: " << "3" << std::endl;
}

std::string CppMetasystem::GetComponentCategory(const std::string& filepath)
{
	std::ifstream inFile(filepath);
	FileBuffer buffer = LFileOperations::ReadTrimmedFileToBuffer(inFile);

	char* temp = "COMPONENT_CATEGORY(";
	size_t componentCategory = buffer.Find("COMPONENT_CATEGORY(");
	if (componentCategory != std::string::npos)
	{
		size_t endParen = buffer.Find(')', componentCategory);
		return buffer.Substr(componentCategory + 20, endParen - 2);
	}

	return "Custom";
}

void CppMetasystem::GenerateLibraryMetadata(const std::string& filepath, std::ofstream& outFile)
{
	// Library Name
}
