#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Containers/THashtable.h"

class TagEditor : public EditorModule
{
	std::vector<TPair<uint16_t, std::string>> tags;
public:
	TagEditor();

	virtual void Display() override;
};