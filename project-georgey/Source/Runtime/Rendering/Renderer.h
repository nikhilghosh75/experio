#pragma once
#include "../../Engine.h"
#include <string>;

class Renderer
{
private:
	unsigned int CompileShader(const std::string& source, unsigned int type);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	Renderer();
	~Renderer();

	void TempRenderer();
};

