#pragma once

#include "../Core/EditorModule.h"

class SceneHierarchy : public EditorModule
{
	std::string currentlySelectedItem;
public:
	SceneHierarchy();

	virtual void Display() override;
};