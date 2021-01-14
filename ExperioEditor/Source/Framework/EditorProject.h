#pragma once
#include <string>
#include "ComponentInfo.h"
#include "ShaderInfo.h"
#include "Version.h"
#include "Runtime/Containers/THashtable.h"

class CodeProject;
class CodeClass;
struct FVersion;

struct FEditorProjectLanguages
{
	uint8_t cppVersion;
	uint16_t glslVersion; // Stored as preprocessor
};

class EditorProject
{
public:
	static THashtable<unsigned int, FComponentInfo> componentClasses;
	static std::vector<FShaderInfo> shaders;

	static std::vector<std::string> gameCompileFiles;
	static CodeProject gameProject;

	static std::string projectName;
	static std::string username;
	static FVersion experioVersion;

	static FEditorProjectLanguages languages;

	static CodeClass& GetClassOfId(unsigned int id);

	static void ReadProjectFile(const std::string& filepath);

	static void ReadUserFile(const std::string& userFilepath);

	static void ReadValueFiles();

	static void SetupRuntimeCompilation();

	static void TempSetup();

	static void TempSetupClasses();

	static void TempSetupMaterials();
};

unsigned int DefaultClassStringToInt(std::string name);