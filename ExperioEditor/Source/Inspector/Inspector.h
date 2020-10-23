#pragma once

#include "../Core/EditorModule.h"

class Inspector : public EditorModule
{

public:
	Inspector();

	virtual void Display() override;
};