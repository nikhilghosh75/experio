#pragma once

#include "../Core/EditorModule.h"

class InputDebugger : public EditorModule
{
public:
	InputDebugger();

	virtual void Display() override;

private:
	void MouseDebugger();

	void KeyboardDebugger();
};