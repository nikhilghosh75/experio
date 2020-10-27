#pragma once

#include "../ComponentEditor.h"
#include "Runtime/Camera/VirtualCamera.h"

class VirtualCameraEditor : COMPONENTEDITOR(VirtualCamera)
{
	virtual unsigned int GetComponentID() const override { return 100; }

	virtual void Display(Component* virtualCamera) override;
};