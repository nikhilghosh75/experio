#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Containers/THashtable.h"

class LayerEditor : public EditorModule
{
	std::vector<TPair<uint16_t, std::string>> layers;
	
	static void OnValuesChanged();
public:
	static LayerEditor* layerEditor;

	LayerEditor();

	virtual void Display() override;
};