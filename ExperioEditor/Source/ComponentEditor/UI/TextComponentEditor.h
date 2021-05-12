#pragma once

#include "../ComponentEditor.h"
#include "Runtime/UI/TextComponent.h"

class TextComponentEditor : COMPONENTEDITOR(TextComponent)
{
	virtual unsigned int GetComponentID() const override { return 104; }

	virtual void Display(Component* component) override;
};