#include "CreateMenu.h"
#include "CreateSystem.h"
#include "../FileView/FileView.h"
#include "imgui.h"
#include <fstream>

bool CreateMenu::cppCreateMenu = false;
bool CreateMenu::materialCreateMenu = false;

ECodeClassBase CreateMenu::currentClassType;

static std::string className = "NewClass";
static std::string materialName = "New Material";

void CreateMenu::Initialize()
{
	className.reserve(64);
}

void CreateMenu::DisplayCreateMenu()
{
	DisplayCPPCreateMenu();
	DisplayMaterialCreateMenu();
}

void CreateMenu::DisplayCPPCreateMenu()
{
	if (ImGui::BeginPopupModal("Create C++ Class", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		std::string filepath = FileView::fileView->GetSelectedFilepath() + "/" + className;

		ImGui::Text("Select a C++ class to derive from");

		ImGui::Separator();

		DisplayClassType("None", "This class is not derived from any class or struct", ECodeClassBase::None);
		DisplayClassType("Component", "This is a component that goes on a Game Object", ECodeClassBase::Component);
		DisplayClassType("System", "This is a system that updates on components. It doesn't go on a game object, but is updated each frame", ECodeClassBase::System);
		DisplayClassType("Library", "This is a library of static functions, which will interface well with Experio's scripting langagues", ECodeClassBase::Library);

		ImGui::Separator();

		ImGui::Text("Base Class: ");
		ImGui::SameLine();
		ImGui::Text(CodeClassBaseToString(currentClassType).c_str());

		ImGui::Text("C++ Filepath: ");
		ImGui::SameLine();
		ImGui::Text((filepath + ".cpp").c_str());

		ImGui::Text("H Filepath: ");
		ImGui::SameLine();
		ImGui::Text((filepath + ".h").c_str());

		ImGui::InputText("Class Name: ", className.data(), className.capacity());

		if (ImGui::Button("Create"))
		{
			CreateSystem::CreateCppClass(filepath + ".h", currentClassType, className);
			CreateSystem::CreateCppClass(filepath + ".cpp", currentClassType, className);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			currentClassType = ECodeClassBase::None;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void CreateMenu::DisplayMaterialCreateMenu()
{
	if (ImGui::BeginPopupModal("Create Material"))
	{
		std::string filepath = FileView::fileView->GetSelectedFilepath() + "/" + materialName;
		ImGui::InputText("Material Name: ", materialName.data(), materialName.capacity());

		if (ImGui::Button("Create"))
		{
			CreateSystem::CreateBasicMaterial(filepath);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void CreateMenu::DisplayClassType(const std::string & name, const std::string & tooltipName, ECodeClassBase classBase)
{
	if (ImGui::Button(name.c_str()))
	{
		currentClassType = classBase;
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip(tooltipName.c_str());
	}
}

std::string CreateMenu::CodeClassBaseToString(ECodeClassBase base)
{
	switch (base)
	{
	case ECodeClassBase::None: return "None";
	case ECodeClassBase::Component: return "Component";
	case ECodeClassBase::Library: return "Library";
	case ECodeClassBase::System: return "System";
	}
	return "";
}
