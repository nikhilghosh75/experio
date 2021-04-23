#pragma once
#include "Shader.h"
#include <string>
#include <sstream>
#include <vector>

struct FShaderDataInternal
{
	std::vector<std::string> shaders;
	std::vector<EShaderType> shaderTypes;
	EShaderLanguage language;
	uint16_t languageVersion;
};

class ShaderReader
{
public:
	static Shader* ReadShader(const std::string& filepath);

	static FShaderDataInternal ParseShader(const std::string& filepath);

	static std::string LanguageToString(EShaderLanguage language);

private:
	static unsigned int CompileShader(const std::string & source, unsigned int type);

	static unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);

	static EShaderLanguage GetLanguageFromString(const std::string& languageType);

	static EShaderType GetShaderType(const std::string& shaderType);

	static bool IsLanguagePreprocessor(const char* preprocessor);

	static bool IsVersionPreprocessor(const char* preprocessor);

	static bool IsShaderPreprocessor(const char* preprocessor);

	static void AddShaderHeader(EShaderLanguage language, uint16_t version, std::stringstream& ss);

	static std::string& GetVertexShader(FShaderDataInternal& shaderData);

	static std::string& GetFragmentShader(FShaderDataInternal& shaderData);

	static bool IsShaderEmpty(const FShaderDataInternal& shaderData);
};