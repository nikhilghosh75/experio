#include "ValueSaver.h"
#include "EditorProject.h"
#include "../Core/EditorApplication.h"
#include <fstream>

void ValueSaver::SaveValues()
{
	SaveValue(EValueType::Layer);
	SaveValue(EValueType::Tag);
}

void ValueSaver::SaveValue(EValueType type)
{
	THashtable<uint16_t, std::string>& table = ExperioEditor::GetTable(type);

	std::ofstream outFile(TypeToFileName(type));
	outFile << "EXPERIO PROJECT VALUES" << std::endl;
	outFile << "Project Name: " << EditorProject::projectName << std::endl;
	outFile << "Version: " << "Versionless" << std::endl;
	outFile << std::endl;

	outFile << TypeToName(type) << " " << table.GetSize() << std::endl;
	table.ForEach([&outFile](uint16_t& index, std::string& name) 
	{
		Debug::Log(std::to_string(name.size()));
		outFile << index << " " << name << std::endl; 
	});
}

std::string ValueSaver::TypeToFileName(EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		return EditorApplication::configFilePath + "/layers.pbvalues";
	case EValueType::Tag:
		return EditorApplication::configFilePath + "/tags.pbvalues";
	}
	return "";
}

std::string ValueSaver::TypeToName(EValueType type)
{
	switch (type)
	{
	case EValueType::Layer:
		return "Layers";
	case EValueType::Tag:
		return "Tags";
	}
	return "";
}
