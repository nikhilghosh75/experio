#include "EditorProject.h"
#include "ValueLoader.h"
#include <fstream>
#include "../Core/EditorApplication.h"
#include "Runtime/Files/LFileOperations.h"
#include "ThirdParty/toml++/toml.h"

THashtable<unsigned int, std::string> EditorProject::classes;
FVersion EditorProject::experioVersion;
std::string EditorProject::projectName;
std::string EditorProject::username;
std::vector<std::string> EditorProject::gameCompileFiles;
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
	EditorProject::classes.Insert(100, "VirtualCamera");
	EditorProject::classes.Insert(101, "MeshComponent");
	EditorProject::classes.Insert(102, "ParticleSystem");
	EditorProject::classes.Insert(103, "Billboard");
	EditorProject::classes.Insert(104, "TextComponent");
}
