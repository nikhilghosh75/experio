#pragma once
#include "../Core/EditorModule.h"

class AdminTools : public EditorModule
{
	bool isAdmin;
public:
	AdminTools();

	virtual void Display() override;
};