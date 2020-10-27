#pragma once

#include "../ComponentEditor.h"
#include "Runtime/Rendering/Components/Billboard.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

class BillboardEditor : COMPONENTEDITOR(Billboard)
{
	virtual unsigned int GetComponentID() const override { return 103; }
public:
	virtual void Display(Component* billboard) override;
};