#pragma once
#include <string>
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"

enum class EShaderType
{
	None = 0,
	Vertex = 1,
	Fragment = 2,
};

enum class EShaderLanguage
{
	None = 0,
	GLSL = 1,
	HLSL = 2
};

class Shader
{
private:
	unsigned int rendererID;

	static uint32_t numShadersLoaded;

public:
	Shader();
	Shader(unsigned int rendererID);

	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniformInt(const std::string& name, int i) const;
	void SetUniformFloat(const std::string& name, float f) const;
	void SetUniformVec2(const std::string& name, glm::vec2 vec) const;
	void SetUniformVec3(const std::string& name, glm::vec3 vec) const;
	void SetUniformVec4(const std::string& name, glm::vec4 vec) const;
	void SetUniformMatrix2(const std::string& name, glm::mat2 mat) const;
	void SetUniformMatrix3(const std::string& name, glm::mat3 mat) const;
	void SetUniformMatrix4(const std::string& name, glm::mat4 mat) const;

	unsigned int GetUniformLocation(const std::string& name) const;
	bool DoesUniformExist(const std::string& name) const;

	static size_t SizeOfLoadedShaders();
};