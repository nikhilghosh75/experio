#include "EditorProject.h"
#include "MetaSystem.h"
#include "ValueLoader.h"
#include <fstream>
#include "../Core/EditorApplication.h"
#include "../CodeParser/CodeParser.h"
#include "../CodeParser/CodeProjectReader.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Framework/Project.h"
#include "ThirdParty/Simdjson/simdjson.h"
#include "ThirdParty/toml++/toml.h"
#include "imgui.h"
#include <filesystem>
namespace fs = std::filesystem;

#define PB_CUSTOM_COMPONENT_INDEX 1024

THashtable<unsigned int, FComponentInfo> EditorProject::componentClasses;
CategoryMap<unsigned int> EditorProject::componentCategories;
std::vector<FShaderInfo> EditorProject::shaders;
FVersion EditorProject::experioVersion(0, 11, 0);
CodeProject EditorProject::gameProject(ECodingLanguage::CPlusPlus);

std::string EditorProject::projectName;
std::string EditorProject::username;
std::vector<std::string> EditorProject::gameCompileFiles;
FEditorProjectLanguages EditorProject::languages;

// This will be deleted later
bool EditorProject::isLayoutQueued = false;
EEditorLayout EditorProject::layoutToSet;

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

void EditorProject::BeginFrame()
{
}

void EditorProject::EndFrame()
{
	if (isLayoutQueued)
	{
		SetLayout(layoutToSet);
		isLayoutQueued = false;
	}
}

CodeClass & EditorProject::GetClassOfId(unsigned int id)
{
	return gameProject.classes[gameProject.FindIndexOfClass(componentClasses.Get(id).name)];
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

void EditorProject::SetProjectPaths()
{
	Project::projectAssetsPath = EditorApplication::assetsFilePath;
	Project::experioResourcesPath = EditorApplication::experioFilePath + "/Resources";
}

void EditorProject::ReadValueFiles()
{
	ValueLoader::LoadValues(EditorApplication::configFilePath + "/layers.pbvalues");
	ValueLoader::LoadValues(EditorApplication::configFilePath + "/tags.pbvalues");
}

void EditorProject::Setup()
{
	SetupClasses();
}

void EditorProject::SetupClasses()
{
	// Create the game project
	gameProject.filepath = EditorApplication::sourceFilePath;
	gameProject.Generate();

	// Import the engine components
	// Code project reader is not working
	// CodeProject engineProject = CodeProjectReader::ReadFromFile(EditorApplication::generatedFilePath + "/Engine.pbcodeproj");
	// LCodeParser::MergeCodeProjects(gameProject, engineProject);

	// Import component classes
	ReadComponents();
	FindComponents();
}

void EditorProject::SetupRuntimeCompilation()
{
	gameCompileFiles = LFileOperations::GetAllFilepathsOfExt(EditorApplication::sourceFilePath, "cpp");
}

void EditorProject::TempSetupClasses()
{
	/**/
	EditorProject::componentClasses.Insert(100, FComponentInfo("VirtualCamera", false));
	EditorProject::componentClasses.Insert(101, FComponentInfo("MeshComponent", true));
	EditorProject::componentClasses.Insert(102, FComponentInfo("ParticleSystem", true));
	EditorProject::componentClasses.Insert(103, FComponentInfo("Billboard", true));
	EditorProject::componentClasses.Insert(104, FComponentInfo("TextComponent", true));
	EditorProject::componentClasses.Insert(105, FComponentInfo("ImageComponent", true));

	gameProject.filepath = EditorApplication::sourceFilePath;
	gameProject.Generate();

	CodeClass virtualCamera("VirtualCamera");
	virtualCamera.inheritance.push_back("Component");
	virtualCamera.params.emplace_back("float", "priority", ECodeAccessType::Public);
	virtualCamera.params.emplace_back("float", "fieldOfView", ECodeAccessType::Public);
	virtualCamera.params.emplace_back("float", "nearClipPlane", ECodeAccessType::Public);
	virtualCamera.params.emplace_back("float", "farClipPlane", ECodeAccessType::Public);

	CodeClass meshComponent("MeshComponent");
	meshComponent.inheritance.push_back("Component");
	meshComponent.params.emplace_back("MeshMaterial*", "material", ECodeAccessType::Public);
	meshComponent.params.emplace_back("MeshRef", "meshData", ECodeAccessType::Public);
	meshComponent.params.emplace_back("bool", "isVisible", ECodeAccessType::Public);

	CodeClass particleSystem("ParticleComponent");
	particleSystem.inheritance.push_back("Component");

	CodeClass billboard("Billboard");
	billboard.inheritance.push_back("Component");
	billboard.params.emplace_back("TextureRef", "billboardTexture", ECodeAccessType::Public);
	billboard.params.emplace_back("EBillboardSizeType", "sizeType", ECodeAccessType::Public);
	billboard.params.emplace_back("EBilboardOrientation", "orientation", ECodeAccessType::Public);
	billboard.params.emplace_back("FVector2", "billboardSize", ECodeAccessType::Public);

	CodeClass textComponent("TextComponent");
	textComponent.inheritance.push_back("Component");
	textComponent.params.emplace_back("float", "margins", ECodeAccessType::Public);
	textComponent.params.emplace_back("int", "fontSize", ECodeAccessType::Public);
	textComponent.params.emplace_back("FontRef", "font", ECodeAccessType::Public);
	textComponent.params.emplace_back("std::string", "text", ECodeAccessType::Public);
	textComponent.params.emplace_back("FColor", "color", ECodeAccessType::Public);
	textComponent.params.emplace_back("EHorizontalWrapMode", "horizontalWrapMode", ECodeAccessType::Public);
	textComponent.params.emplace_back("EVerticalWrapMode", "verticalWrapMode", ECodeAccessType::Public);
	textComponent.params.emplace_back("EHorizontalAlignment", "horizontalAlignment", ECodeAccessType::Public);
	textComponent.params.emplace_back("EVerticalAlignment", "verticalAlignment", ECodeAccessType::Public);
	textComponent.params.emplace_back("float", "spacing", ECodeAccessType::Public);
	textComponent.params.emplace_back("Shader*", "shader", ECodeAccessType::Public);
	textComponent.params.emplace_back("std::string", "text", ECodeAccessType::Public);

	CodeClass imageComponent("ImageComponent");
	imageComponent.inheritance.emplace_back("Component");
	imageComponent.params.emplace_back("TextureRef", "texture", ECodeAccessType::Public);
	imageComponent.params.emplace_back("FColor", "tint", ECodeAccessType::Public);

	CodeClass progressBar("ProgressBar");
	progressBar.inheritance.emplace_back("Component");
	progressBar.params.emplace_back("float", "minValue", ECodeAccessType::Public);
	progressBar.params.emplace_back("float", "maxValue", ECodeAccessType::Public);
	progressBar.params.emplace_back("float", "value", ECodeAccessType::Public);
	progressBar.params.emplace_back("FColor", "backgroundColor", ECodeAccessType::Public);
	progressBar.params.emplace_back("FColor", "barColor", ECodeAccessType::Public);
	progressBar.params.emplace_back("Shader*", "shader", ECodeAccessType::Public);
	progressBar.params.emplace_back("EProgressBarMode", "mode", ECodeAccessType::Public);

	CodeClass panel("Panel");
	panel.inheritance.emplace_back("Component");
	panel.params.emplace_back("float", "roundedPixels", ECodeAccessType::Public);
	panel.params.emplace_back("FColor", "color", ECodeAccessType::Public);
	panel.params.emplace_back("TextureRef", "texture", ECodeAccessType::Public);

	// Delete Later
	EditorProject::componentClasses.Insert(1024, FComponentInfo("Spaceship", "Components/Spaceship.h", true, false));

	CodeEnum spaceshipType("ESpaceshipType", EEnumDataType::INT);
	spaceshipType.values.Insert(0, "Red");
	spaceshipType.values.Insert(1, "Blue");
	spaceshipType.values.Insert(2, "Green");
	gameProject.PushEnum(spaceshipType);
	// End Delete Later

	gameProject.PushClass(virtualCamera);
	gameProject.PushClass(meshComponent);
	gameProject.PushClass(particleSystem);
	gameProject.PushClass(billboard);
	gameProject.PushClass(textComponent);
	gameProject.PushClass(imageComponent);
	gameProject.PushClass(progressBar);
	gameProject.PushClass(panel);

	gameProject.EmplaceEnum("EBillboardSizeType", EEnumDataType::UBYTE);
	gameProject.EmplaceEnum("EBilboardOrientation", EEnumDataType::UBYTE);
	gameProject.EmplaceEnum("EHorizontalWrapMode", EEnumDataType::UBYTE);
	gameProject.EmplaceEnum("EVerticalWrapMode", EEnumDataType::UBYTE);
	gameProject.EmplaceEnum("EHorizontalAlignment", EEnumDataType::UBYTE);
	gameProject.EmplaceEnum("EVerticalAlignment", EEnumDataType::UBYTE);
	gameProject.EmplaceEnum("EProgressBarMode", EEnumDataType::UBYTE);
}

void EditorProject::TempSetupMaterials()
{
	FShaderInfo basic("Basic");
	basic.EmplaceUniform(EShaderParamType::TEXTURE, "albedo");
	basic.EmplaceUniform(EShaderParamType::TEXTURE, "normal");
	basic.EmplaceUniform(EShaderParamType::TEXTURE, "specular");
	shaders.push_back(basic);
}

void EditorProject::SetLayout(EEditorLayout layout)
{
	switch (layout)
	{
	case EEditorLayout::Default: SetLayoutDefault(); break;
	case EEditorLayout::Tall: SetLayoutTall(); break;
	case EEditorLayout::Wide: SetLayoutWide(); break;
	}
}

void EditorProject::QueueSetLayout(EEditorLayout layout)
{
	isLayoutQueued = true;
	layoutToSet = layout;
}

void EditorProject::SetLayoutDefault()
{
	ImGui::LoadIniSettingsFromDisk((EditorApplication::experioEditorFilePath + "/Resources/Layouts/Default.ini").c_str());
}

void EditorProject::SetLayoutTall()
{
	ImGui::LoadIniSettingsFromDisk((EditorApplication::experioEditorFilePath + "/Resources/Layouts/Tall.ini").c_str());
}

void EditorProject::SetLayoutWide()
{
	ImGui::LoadIniSettingsFromDisk((EditorApplication::experioEditorFilePath + "/Resources/Layouts/Wide.ini").c_str());
}

void EditorProject::ReadComponents()
{
	componentClasses.Empty();

	std::string componentsFilepath = EditorApplication::generatedFilePath + "/Components.json";
	simdjson::ondemand::parser parser;
	simdjson::padded_string jsonStr = simdjson::padded_string::load(componentsFilepath);
	simdjson::ondemand::document json = parser.iterate(jsonStr);

	auto components = json["Components"];
	for (auto it : components)
	{
		unsigned int id = it["id"].get_uint64();

		FComponentInfo info;
		info.name = it["name"].get_string().value();
		info.filepath = it["filepath"].get_string().value();
		info.stage = (EComponentStage)it["stage"].get_int64().value();
		info.category = it["category"].get_string().value();
		info.isDefaultComponent = it["default"].get_bool().value();
		info.isStandaloneComponent = it["standalone"].get_bool().value();

		componentClasses.Insert(id, info);
		componentCategories.Insert(info.category, id);
	}
}

void EditorProject::FindComponents()
{
	for (auto& p : fs::recursive_directory_iterator(EditorApplication::sourceFilePath))
	{
		std::string pathString = p.path().string();
		EAssetType type = LFileOperations::GetFileType(pathString);
		if (type == EAssetType::CPP)
		{
			std::string metaFilepath = pathString.substr(0, pathString.size() - 4);
			Metadata metadata = MetaSystem::ReadMetadata(metaFilepath);
			if (metadata.Empty())
				continue;

			if (metadata["ClassType"] == "Component")
			{
				unsigned int id = LString::StringToUInt(metadata["ComponentID"]);

				FComponentInfo info;
				info.name = metadata["ComponentName"];
				info.filepath = LFileOperations::ReplaceExtension(pathString, "h");
				info.stage = (EComponentStage)LString::StringToUByte(metadata["Stage"]);
				info.category = metadata["Category"];
				info.isDefaultComponent = false;
				info.isStandaloneComponent = LString::StringToBool(metadata["Standalone"]);

				componentClasses.Insert(id, info);
				componentCategories.Insert(info.category, id);
			}
		}
	}
}

unsigned int EditorProject::GetNextComponentIndex()
{
	std::vector<unsigned int> componentIndicies = componentClasses.GetKeys();

	unsigned int maxIndex = 0;
	for (size_t i = 0; i < componentIndicies.size(); i++)
	{
		if (maxIndex < componentIndicies[i])
			maxIndex = componentIndicies[i];
	}

	if (maxIndex < PB_CUSTOM_COMPONENT_INDEX)
		return PB_CUSTOM_COMPONENT_INDEX;

	return maxIndex + 1;
}
