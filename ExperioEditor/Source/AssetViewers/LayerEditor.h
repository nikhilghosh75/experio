#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Containers/THashtable.h"

class LayerEditor : public EditorModule
{
	std::vector<TPair<uint16_t, std::string>> layers;
public:
	LayerEditor();

	virtual void Display() override;
};