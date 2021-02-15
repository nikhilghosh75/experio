#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Containers/THashtable.h"

class TagEditor : public EditorModule
{
	std::vector<TPair<uint16_t, std::string>> tags;

	static void OnValuesChanged();
public:
	static TagEditor* tagEditor;

	TagEditor();

	virtual void Display() override;
};