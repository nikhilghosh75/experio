#pragma once
#include <string>
#include "ComponentInfo.h"
#include "ShaderInfo.h"
#include "Version.h"
#include "Runtime/Containers/THashtable.h"
#include "Runtime/Data/CategoryMap.h"

class CodeProject;
class CodeClass;
struct FVersion;

struct FEditorProjectLanguages
{
	uint8_t cppVersion;
	uint16_t glslVersion; // Stored as preprocessor
};

enum class EEditorLayout
{
	Default,
	Tall,
	Wide
};

class EditorProject
{
public:
	static THashtable<unsigned int, FComponentInfo> componentClasses;
	static CategoryMap<unsigned int> componentCategories;

	static std::vector<FShaderInfo> shaders;

	static std::vector<std::string> gameCompileFiles;
	static CodeProject gameProject;

	static std::string projectName;
	static std::string username;
	static FVersion experioVersion;

	static FEditorProjectLanguages languages;

	static void BeginFrame();
	static void EndFrame();

	static CodeClass& GetClassOfId(unsigned int id);

	static void ReadProjectFile(const std::string& filepath);

	static void ReadUserFile(const std::string& userFilepath);

	static void SetProjectPaths();

	static void ReadValueFiles();

	static void Setup();

	static void SetupClasses();

	static void SetupRuntimeCompilation();

	static void TempSetupClasses();

	static void TempSetupMaterials();

	// Layouts
	static void SetLayout(EEditorLayout layout);

	static void QueueSetLayout(EEditorLayout layout);

	static void ReadComponents();

private:
	static void SetLayoutDefault();
	static void SetLayoutTall();
	static void SetLayoutWide();

	// This needs to be replaced with a better system later
	static bool isLayoutQueued;
	static EEditorLayout layoutToSet;
};

unsigned int DefaultClassStringToInt(std::string name);