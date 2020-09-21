#pragma once

#include "../Core/EditorModule.h"
#include "imgui.h"

class TestModule : public EditorModule
{
	virtual void Display() override
	{
		ImGui::Text("Hello World");
		ImGui::ColorButton("Test Button", ImVec4(1, 0, 0, 0));
		
		if (ImGui::TreeNode("Tree 1", "Tree Tile"))
		{
			ImGui::Text("Inside Tree");
			ImGui::TreePop();
		}
	}
};