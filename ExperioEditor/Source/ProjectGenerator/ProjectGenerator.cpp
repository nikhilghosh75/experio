#include "ProjectGenerator.h"
#include "VisualStudioProject.h"
#include "EditorCodeGenerator.h"
#include "../Core/EditorApplication.h"
#include "../Framework/EditorProject.h"
#include "ThirdParty/toml++/toml.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace ExperioEditor::ProjectGenerator
{

void GenerateWindowsProject(const std::string & projectPath, const FNewProjectSettings & settings)
{
	VisualStudio::VSSolution solution;
	GenerateGameProject(projectPath, settings.projectName, solution);
	GenerateEditorProject(projectPath, settings.projectName, solution);
	GenerateExeProject(projectPath, settings.projectName, solution);
	solution.GenerateSolutionFile(projectPath);

	GenerateUserFile(projectPath, settings);
	GenerateProjectFile(projectPath, settings);
	GenerateFolders(projectPath);
	GenerateConfig(projectPath, settings.projectName, settings.version);
	
	GenerateCode(projectPath);
}

void GenerateGameProject(const std::string & gamePath, const std::string& projectName, VisualStudio::VSSolution& solution)
{
	VisualStudio::VSProject project(projectName);

	project.projectType = VisualStudio::EVSProjectType::Cpp;
	project.architecture = EArchitecture::x64;
	project.SetConfiguration(VisualStudio::EVSConfiguration::DynamicLibrary);
	project.language = ECodingLanguage::CPlusPlus;
	project.version = 17;

	project.outputDirectory = gamePath + "/Binaries/Game";
	project.intermediateDirectory = gamePath + "/Binaries/Game/Intermediate";
	
	project.preprocessorDefines = { "PLATFORM_WINDOWS" };
	project.additionalIncludeDirectories = { EditorApplication::experioFilePath, EditorApplication::experioDependenciesFilePath };

	std::stringstream filename;
	filename << gamePath << "/" << projectName << ".vcxproj";
	project.filepath = filename.str();
	project.GenerateProjectFile(filename.str());
	solution.projects.push_back(project);
}

void GenerateEditorProject(const std::string & projectPath, const std::string& projectName, VisualStudio::VSSolution& solution)
{
	VisualStudio::VSProject project(projectName + "_Editor");

	project.projectType = VisualStudio::EVSProjectType::Cpp;
	project.architecture = EArchitecture::x64;
	project.SetConfiguration(VisualStudio::EVSConfiguration::Executable);
	project.language = ECodingLanguage::CPlusPlus;
	project.version = 17;

	project.outputDirectory = projectPath + "/Binaries/Editor";
	project.intermediateDirectory = projectPath + "/Binaries/Editor/Intermediate";

	project.preprocessorDefines = { "PLATFORM_WINDOWS", "EXPERIO_EDITOR" };
	project.additionalIncludeDirectories = { EditorApplication::experioFilePath,
		EditorApplication::experioEditorFilePath, EditorApplication::experioDependenciesFilePath };

	std::stringstream filename;
	filename << projectPath << "/Editor/" << projectName << "_Editor.vcxproj";
	project.filepath = filename.str();
	project.GenerateProjectFile(filename.str());
	solution.projects.push_back(project);
}

void GenerateExeProject(const std::string& projectPath, const std::string& projectName, VisualStudio::VSSolution& solution)
{
	VisualStudio::VSProject project(projectName + "_Exe");

	project.projectType = VisualStudio::EVSProjectType::Cpp;
	project.architecture = EArchitecture::x64;
	project.SetConfiguration(VisualStudio::EVSConfiguration::Executable);
	project.language = ECodingLanguage::CPlusPlus;
	project.version = 17;

	project.outputDirectory = projectPath + "/Binaries/Exe";
	project.intermediateDirectory = projectPath + "/Binaries/Exe/Intermediate";

	project.preprocessorDefines = { "PLATFORM_WINDOWS" };
	project.additionalIncludeDirectories = { EditorApplication::experioFilePath,
		EditorApplication::experioEditorFilePath, EditorApplication::experioDependenciesFilePath };

	std::stringstream filename;
	filename << projectPath << "/Generated/" << projectName << "_Exe.vcxproj";
	project.filepath = filename.str();
	project.GenerateProjectFile(filename.str());
	solution.projects.push_back(project);
}

void GenerateUserFile(const std::string & projectPath, const FNewProjectSettings & settings)
{
	toml::table table;

	table.insert("Username", settings.username);

	toml::table filepaths;
	filepaths.insert("Experio", settings.experioPath);
	filepaths.insert("ExperioEditor", settings.experioEditorPath);
	filepaths.insert("Binaries", settings.experioBinariesPath);
	filepaths.insert("Dependencies", settings.experioDependenciesPath);

	table.insert("Filepaths", filepaths);

	std::stringstream filename;
	filename << projectPath << "/user.pbuser";
	std::ofstream outFile(filename.str());
	outFile << table;
}

void GenerateProjectFile(const std::string & projectPath, const FNewProjectSettings & settings)
{
	toml::table table;

	table.insert("ProjectName", settings.projectName);
	table.insert("Experio", EditorProject::experioVersion.ToString());

	toml::table filepaths;
	filepaths.insert("Assets", "../Assets");
	filepaths.insert("Binaries", "../Binaries");
	filepaths.insert("Config", "../Config");
	filepaths.insert("Editor", "");
	filepaths.insert("Generated", "../Generated");
	filepaths.insert("Source", "../Source");

	toml::table languages;
	languages.insert("Cpp", 17);
	languages.insert("GLSL", 460);

	toml::table defaults;
	defaults.insert("Scenes", "../Assets/Scenes/TestScene.pbscene");

	table.insert("Filepaths", filepaths);
	table.insert("Languages", languages);
	table.insert("Defaults", defaults);

	std::stringstream filename;
	filename << projectPath << "/" << settings.projectName << ".pbproj";
	std::ofstream outFile(filename.str());
	outFile << table;
}

void GenerateFolders(const std::string & projectPath)
{
	std::filesystem::create_directory(projectPath + "/Assets");
	std::filesystem::create_directory(projectPath + "/Assets/Scenes");

	std::filesystem::create_directory(projectPath + "/Binaries");
	std::filesystem::create_directory(projectPath + "/Binaries/Editor");
	std::filesystem::create_directory(projectPath + "/Binaries/Exe");
	std::filesystem::create_directory(projectPath + "/Binaries/Intermediate");

	std::filesystem::create_directory(projectPath + "/Config");

	std::filesystem::create_directory(projectPath + "/Editor");
	std::filesystem::create_directory(projectPath + "/Editor/RCCPP");

	std::filesystem::create_directory(projectPath + "/Generated");

	std::filesystem::create_directory(projectPath + "/Source");
	std::filesystem::create_directory(projectPath + "/Source/Components");
}

void GenerateConfig(const std::string & projectPath, const std::string& projectName, FVersion version)
{
	GenerateTagFile(projectPath + "/Config/tags.pbvalues", projectName, version);
	GenerateLayerFile(projectPath + "/Config/layers.pbvalues", projectName, version);
}

void GenerateTagFile(const std::string & filepath, const std::string& projectName, FVersion version)
{
	std::ofstream outFile;
	outFile << "EXPERIO PROJECT VALUES" << std::endl;
	outFile << "Project Name: " << projectName << std::endl;
	outFile << "Version: " << version << std::endl;
	outFile << std::endl;
	outFile << "Tags 1" << std::endl;
	outFile << "0 Default" << std::endl;
}

void GenerateLayerFile(const std::string & filepath, const std::string& projectName, FVersion version)
{
	std::ofstream outFile;
	outFile << "EXPERIO PROJECT VALUES" << std::endl;
	outFile << "Project Name: " << projectName << std::endl;
	outFile << "Version: " << version << std::endl;
	outFile << std::endl;
	outFile << "Layers 1" << std::endl;
	outFile << "0 Default" << std::endl;
}

void GenerateCode(const std::string & projectPath)
{
	EditorCodeGenerator::GenerateBuild(projectPath + "/Editor");
	EditorCodeGenerator::GenerateRCCPP(projectPath + "/Editor");
	EditorCodeGenerator::GenerateMain(projectPath + "/Editor");

	EditorCodeGenerator::GenerateExecutable(projectPath + "/Generated");
}

}
