#include "CreateMenu.h"
#include "imgui.h"
#include "EditorProject.h"
#include <fstream>

bool CreateMenu::cppCreateMenu = false;
bool CreateMenu::materialCreateMenu = false;

void CreateMenu::DisplayCreateMenu()
{
	DisplayCPPCreateMenu();
	DisplayMaterialCreateMenu();
}

void CreateMenu::CreateDatatable(const std::string& filepath)
{
	std::ofstream outFile(filepath + "/data.csv");
}

void CreateMenu::CreateScene(const std::string & filepath)
{
	std::ofstream outFile(filepath + "/scene.pbscene");
	outFile << "PROJECT BLOO SCENE" << std::endl;
	outFile << "Name: New Scene" << std::endl;
	outFile << "Project: " << EditorProject::projectName << std::endl;
	outFile << "{ " << std::endl;
	outFile << "	Name: Scene Root" << std::endl;
	outFile << "	Transform : 0 0 0 0 0 0 1 1 1 1" << std::endl;
	outFile << "	Tag : 0" << std::endl;
	outFile << "	Layer : 0" << std::endl;
	outFile << "	Components : [{" << std::endl;
	outFile << "		ClassID: 99" << std::endl;
	outFile << "		Params :" << std::endl;
	outFile << "	Children: []" << std::endl;
	outFile << "}]" << std::endl;
}

void CreateMenu::DisplayCPPCreateMenu()
{
	if (ImGui::BeginPopupModal("Create C++ Class", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Select a C++ class to derive from");

		if (ImGui::Button("None"))
		{
			// Add Stuff Here
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("This class is not derived from any class or struct");
		}

		if (ImGui::Button("Component"))
		{
			// Add Stuff Here
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("This is a component that goes on a Game Object");
		}

		if (ImGui::Button("System"))
		{
			// Add Stuff Here
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip(
				"This is a system that updates on components. It doesn't go on a game object, but is updated each frame"
			);
		}

		if (ImGui::Button("Create"))
		{
			// Add Stuff Here
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void CreateMenu::DisplayMaterialCreateMenu()
{
	if (ImGui::BeginPopupModal("Create Material"))
	{
		ImGui::Text("This has not been created yet.");
		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}
