#pragma once
#include "../Core/EditorModule.h"

class MemoryProfiler : public EditorModule
{
	size_t datatableSize;
	size_t fontSize;
	size_t meshSize;
	size_t textureSize;
	size_t gameObjectSize;
	size_t shaderSize;

	bool shouldCalculate = false;

	void Calculate();

public:
	MemoryProfiler();

	virtual void Display() override;
};