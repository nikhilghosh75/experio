#pragma once
#include "../../Engine.h"
#include <string>;

class Renderer
{
private:
	void LogRenderingError();
public:
	Renderer();
	~Renderer();

	void TempRenderer();
};

