#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Renderer.h"

class SceneView : public EditorModule
{
	Renderer renderer;
public:
	SceneView();

	virtual void Display() override;
};