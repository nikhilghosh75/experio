#include "ShaderReader.h"
#include "GL/glew.h"
#include "../../Containers/LString.h"
#include "../../Debug/Debug.h"
#include "../../Rendering/OpenGL/LOpenGL.h"
#include <fstream>

Shader* ShaderReader::ReadShader(const std::string & filepath)
{
	FShaderDataInternal shaderData = ParseShader(filepath);

	if (IsShaderEmpty(shaderData))
	{
		return nullptr;
	}

	std::string& fragmentShader = GetFragmentShader(shaderData);
	std::string& vertexShader = GetVertexShader(shaderData);
	return new Shader(CreateShader(vertexShader, fragmentShader));
}

unsigned int ShaderReader::CompileShader(const std::string & source, unsigned int type)
{
	if (source.size() < 2)
	{
		Debug::LogError("Shader is empty");
		return 0;
	}
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		Debug::LogError("Failed to compile shader!" + std::string(message));
	}

	return id;
}

unsigned int ShaderReader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

FShaderDataInternal ShaderReader::ParseShader(const std::string& filepath)
{
	FShaderDataInternal shaderData;

	if (filepath.size() == 0)
	{
		return shaderData;
	}

	std::ifstream inFile(filepath);
	char word[256];

	inFile.getline(word, 256);
	if (!IsLanguagePreprocessor(word))
	{
		Debug::LogError("Shader is not a valid shader type");
	}
	shaderData.language = GetLanguageFromString(word + 10);
	std::stringstream ss;
	EShaderType shaderType = EShaderType::None;

	// Extend this later
	while (inFile.getline(word, 256))
	{
		if (word[0] == '#')
		{
			if (IsVersionPreprocessor(word))
			{
				shaderData.languageVersion = LString::StringToUInt(std::string(word + 9));
			}
			else if (IsShaderPreprocessor(word))
			{
				shaderData.shaders.push_back(ss.str());
				shaderData.shaderTypes.push_back(shaderType);

				shaderType = GetShaderType(std::string(word + 8));
				ss.str("");
				AddShaderHeader(shaderData.language, shaderData.languageVersion, ss);
			}
		}
		else
		{
			ss << word << std::endl;
		}
	}

	shaderData.shaders.push_back(ss.str());
	shaderData.shaderTypes.push_back(shaderType);

	return shaderData;
}

std::string ShaderReader::LanguageToString(EShaderLanguage language)
{
	switch (language)
	{
	case EShaderLanguage::None: return "None";
	case EShaderLanguage::GLSL: return "GLSL";
	case EShaderLanguage::HLSL: return "HLSL";
	}
	return "";
}

EShaderLanguage ShaderReader::GetLanguageFromString(const std::string& languageType)
{
	if (languageType== "GLSL") return EShaderLanguage::GLSL;
	if (languageType == "HLSL") return EShaderLanguage::HLSL;
	return EShaderLanguage::None;
}

EShaderType ShaderReader::GetShaderType(const std::string& shaderType)
{
	if (shaderType == "vertex") return EShaderType::Vertex;
	if (shaderType == "fragment") return EShaderType::Fragment;
	return EShaderType::None;
}

bool ShaderReader::IsLanguagePreprocessor(const char * preprocessor)
{
	if (preprocessor[1] == 'l' && preprocessor[2] == 'a' && preprocessor[3] == 'n' && preprocessor[4] == 'g'
		 && preprocessor[5] == 'u' && preprocessor[6] == 'a' && preprocessor[7] == 'g' && preprocessor[8] == 'e')
	{
		return true;
	}
	return false;
}

bool ShaderReader::IsVersionPreprocessor(const char * preprocessor)
{
	if (preprocessor[1] == 'v' && preprocessor[2] == 'e' && preprocessor[3] == 'r'
		&& preprocessor[4] == 's' && preprocessor[5] == 'i' && preprocessor[6] == 'o' && preprocessor[7] == 'n')
	{
		return true;
	}
	return false;
}

bool ShaderReader::IsShaderPreprocessor(const char * preprocessor)
{
	if (preprocessor[1] == 's' && preprocessor[2] == 'h' && preprocessor[3] == 'a'
		&& preprocessor[4] == 'd' && preprocessor[5] == 'e' && preprocessor[6] == 'r')
	{
		return true;
	}
	return false;
}

void ShaderReader::AddShaderHeader(EShaderLanguage language, uint16_t version, std::stringstream & ss)
{
	switch (language)
	{
	case EShaderLanguage::GLSL:
		ss << "#version " << version << std::endl;
		return;
	}
}

std::string& ShaderReader::GetVertexShader(FShaderDataInternal & shaderData)
{
	for (uint8_t i = 0; i < shaderData.shaders.size(); i++)
	{
		if (shaderData.shaderTypes[i] == EShaderType::Vertex) return shaderData.shaders[i];
	}

	return shaderData.shaders[0];
}

std::string& ShaderReader::GetFragmentShader(FShaderDataInternal & shaderData)
{
	for (uint8_t i = 0; i < shaderData.shaders.size(); i++)
	{
		if (shaderData.shaderTypes[i] == EShaderType::Fragment) return shaderData.shaders[i];
	}

	return shaderData.shaders[0];
}

bool ShaderReader::IsShaderEmpty(const FShaderDataInternal& shaderData)
{
	return shaderData.shaders.empty();
}
