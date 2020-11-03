#pragma once

#include "../Core/EditorModule.h"

#include "Runtime/Debug/Debug.h"

class Console : public EditorModule
{
	size_t startIndex = 0;
public:
	Console();

	virtual void Display() override;
};