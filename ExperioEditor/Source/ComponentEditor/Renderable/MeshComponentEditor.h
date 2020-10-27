#pragma once

#include "../ComponentEditor.h"
#include "Runtime/Rendering/Components/MeshComponent.h"

class MeshEditor : COMPONENTEDITOR(MeshComponent)
{
	virtual unsigned int GetComponentID() const override { return 101; }

public:
	virtual void Display(Component* mesh) override;
};
