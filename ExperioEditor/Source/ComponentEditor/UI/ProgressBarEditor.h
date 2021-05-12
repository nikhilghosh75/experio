#pragma once

#include "../ComponentEditor.h"
#include "Runtime/UI/ProgressBar.h"

class ProgressBarEditor : COMPONENTEDITOR(ProgressBar)
{
	virtual unsigned int GetComponentID() const override { return 106; }

	virtual void Display(Component * component) override;
};