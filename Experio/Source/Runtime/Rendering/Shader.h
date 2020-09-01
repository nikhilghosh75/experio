#pragma once
#include <string>
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/glm.hpp"
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/mat4x4.hpp"

enum class EShaderType
{
	Vertex = 0,
	Fragment = 1,
	None = 400
};

class Shader
{
private:
	std::string vertexShaderFilepath, fragmentShaderFilepath;
	unsigned int rendererID;
public:
	Shader();
	Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
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

	static unsigned int CompileShader(const std::string & source, unsigned int type);
	static unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
	static std::string ParseShader(const std::string& filepath);
	unsigned int GetUniformLocation(const std::string& name) const;
	bool DoesUniformExist(const std::string& name) const;
};