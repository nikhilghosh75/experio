#include "EditorProject.h"
#include "ValueLoader.h"
#include <fstream>
#include "../Core/EditorApplication.h"
#include "../CodeParser/CodeParser.h"
#include "Runtime/Files/LFileOperations.h"
#include "ThirdParty/toml++/toml.h"
#include "Version.h"

THashtable<unsigned int, FComponentInfo> EditorProject::componentClasses;
FVersion EditorProject::experioVersion;
// CodeProject EditorProject::gameProject;

std::string EditorProject::projectName;
std::string EditorProject::username;
std::vector<std::string> EditorProject::gameCompileFiles;
FEditorProjectLanguages EditorProject::languages;

unsigned int DefaultClassStringToInt(std::string name)
{
	unsigned int classId;
	FComponentInfo componentInfo;
	if (EditorProject::componentClasses.SearchValues(classId, componentInfo, [name](const FComponentInfo& info) {return info.name == name;}))
	{
		return classId;
	}
	return 0;
}

std::string DefaultClassIntToString(unsigned int num)
{
	FComponentInfo componentInfo;
	if (EditorProject::componentClasses.SafeGet(num, componentInfo))
	{
		return componentInfo.name;
	}
	return "Unknown";
}

void EditorProject::ReadProjectFile(const std::string& filepath)
{
	toml::table table = toml::parse_file(filepath);
	
	// General
	projectName = table["General"]["ProjectName"].value_or("");
	experioVersion = FVersion(table["General"]["Experio"].value_or(""));
	
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

void EditorProject::ReadUserFile(const std::string & userFilepath)
{
	toml::table table = toml::parse_file(userFilepath);

	// General
	username = table["General"]["Username"].value_or("");

	// Filepaths
	EditorApplication::experioFilePath = table["Filepaths"]["Experio"].value_or("");
	EditorApplication::experioEditorFilePath = table["Filepaths"]["ExperioEditor"].value_or("");
	EditorApplication::experioBinariesFilePath = table["Filepaths"]["Binaries"].value_or("");
	EditorApplication::experioDependenciesFilePath = table["Filepaths"]["Dependencies"].value_or("");
}

void EditorProject::ReadValueFiles()
{
	ValueLoader::LoadValues(EditorApplication::configFilePath + "/layers.pbvalues");
	ValueLoader::LoadValues(EditorApplication::configFilePath + "/tags.pbvalues");
}

void EditorProject::SetupRuntimeCompilation()
{
	gameCompileFiles = LFileOperations::GetAllFilepathsOfExt(EditorApplication::sourceFilePath, "cpp");
}

void EditorProject::TempSetup()
{
	EditorProject::componentClasses.Insert(100, FComponentInfo("VirtualCamera", false));
	EditorProject::componentClasses.Insert(101, FComponentInfo("MeshComponent", true));
	EditorProject::componentClasses.Insert(102, FComponentInfo("ParticleSystem", true));
	EditorProject::componentClasses.Insert(103, FComponentInfo("Billboard", true));
	EditorProject::componentClasses.Insert(104, FComponentInfo("TextComponent", true));
}
