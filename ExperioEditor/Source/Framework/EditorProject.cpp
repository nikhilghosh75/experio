#include "EditorProject.h"
#include "ValueLoader.h"
#include <fstream>
#include "../Core/EditorApplication.h"
#include "ThirdParty/toml++/toml.h"

THashtable<unsigned int, std::string> EditorProject::classes;
FVersion EditorProject::experioVersion;
std::string EditorProject::projectName;
FEditorProjectLanguages EditorProject::languages;

unsigned int DefaultClassStringToInt(std::string name)
{
	unsigned int classId;
	if (EditorProject::classes.Find(name, classId))
	{
		return classId;
	}
	return 0;
}

std::string DefaultClassIntToString(unsigned int num)
{
	std::string str;
	if (EditorProject::classes.SafeGet(num, str))
	{
		return str;
	}
	return "Unknown";
}

void EditorProject::ReadProjectFile(std::string filepath)
{
	toml::table table = toml::parse_file(filepath);
	
	// General
	projectName = table["General"]["ProjectName"].value_or("");
	experioVersion = FVersion(table["General"]["Experio"].value_or(""));

	// Languages
	languages.cppVersion = table["Languages"]["Cpp"].value_or(14);
	languages.glslVersion = table["Languages"]["GLSL"].value_or(330);
	
	// Filepaths
	EditorApplication::assetsFilePath = table["Filepaths"]["Assets"].value_or("/Assets");
	EditorApplication::binariesFilePath = table["Filepaths"]["Binaries"].value_or("/Binaries");
	EditorApplication::configFilePath = table["Filepaths"]["Config"].value_or("/Config");
	EditorApplication::editorFilePath = table["Filepaths"]["Editor"].value_or("/Editor");
	EditorApplication::generatedFilePath = table["Filepaths"]["Generated"].value_or("/Generated");
	EditorApplication::sourceFilePath = table["Filepaths"]["Source"].value_or("/Source");

	// Defaults
	EditorApplication::defaultScenePath = table["Defaults"]["Scene"].value_or("");
}

void EditorProject::ReadValueFiles()
{
	ValueLoader::LoadValues(EditorApplication::configFilePath + "/layers.pbvalues");
	ValueLoader::LoadValues(EditorApplication::configFilePath + "/tags.pbvalues");
}

void EditorProject::TempSetup()
{
	EditorProject::classes.Insert(100, "VirtualCamera");
	EditorProject::classes.Insert(101, "MeshComponent");
	EditorProject::classes.Insert(102, "ParticleSystem");
	EditorProject::classes.Insert(103, "Billboard");
	EditorProject::classes.Insert(104, "TextComponent");
}
