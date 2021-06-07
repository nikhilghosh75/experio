#include "InputMapViewer.h"
#include "../Core/FileDialog.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Debug/Profiler.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Input/InputMapReader.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "ThirdParty/Magic Enum/magic_enum.hpp"

InputMapViewer::InputMapViewer()
{
	this->category = EEditorModuleCategory::Viewer;
	this->name = "Input Map Viewer";

	loaded = false;

	categoryIndex = -1;
	configIndex = -1;
	action = false;
	actionIndex = -1;
}

void InputMapViewer::Display()
{
	PROFILE_SCOPE("InputMapViewer::Display");

	if (!loaded)
		DisplayEmpty();
	else
		DisplayInputMap();
}

void InputMapViewer::Load(const std::string& filepath)
{
	this->filepath = filepath;
	this->mapName = LFileOperations::StripFilenameAndExt(filepath);
	this->currentMap = InputMapReader::ReadInputMap(filepath);
	this->loaded = true;
}

void InputMapViewer::DisplayEmpty()
{
	PROFILE_SCOPE("InputMapViewer::DisplayEmpty");
	if (ImGui::Button("Load Input Map"))
	{
		FFileDialogInfo info = FileDialog::OpenFile("Experio Input Map (*.pbipmap)\0*.pbipmap\0");
		if (info.IsValid())
			Load(info.filename);
	}
}

void InputMapViewer::DisplayInputMap()
{
	PROFILE_SCOPE("InputMapViewer::DisplayInputMap");
	ImGui::Text(this->mapName.c_str());
	if (ImGui::Button("Save")) SaveInputMap();

	float width = this->GetWindowSize().x - 25;

	ImGui::BeginChild("Categories", ImVec2(width / 4, 0), true);
	DisplayCategories();
	ImGui::EndChild(); ImGui::SameLine();

	ImGui::BeginChild("Configs", ImVec2(width / 4, 0), true);
	DisplayCategoryInfo();
	DisplayConfigs();
	ImGui::EndChild(); ImGui::SameLine();

	ImGui::BeginChild("Actions + Axes", ImVec2(width / 4, 0), true);
	DisplayConfigInfo();
	DisplayActionsAndAxes();
	ImGui::EndChild(); ImGui::SameLine();

	ImGui::BeginChild("Details", ImVec2(width / 4, 0), true);
	DisplayActionAndAxis();
	ImGui::EndChild();
}

void InputMapViewer::DisplayCategories()
{
	ImGui::Text("Categories:");
	ImGui::Spacing();

	for (int i = 0; i < currentMap.categories.size(); i++)
	{
		bool isSelected = categoryIndex == i;
		bool selected = ImGui::Selectable(currentMap.categories[i].name.c_str(), &isSelected);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::Selectable("Delete"))
			{
				Experio::Algorithm::RemoveAt(currentMap.categories, i);
			}
			ImGui::EndPopup();
		}

		if (selected && categoryIndex != i)
		{
			configIndex = -1;
			categoryIndex = i;
		}
	}

	if (ImGui::Button("+"))
	{
		currentMap.categories.emplace_back("New Category");
	}
}

void InputMapViewer::DisplayCategoryInfo()
{
	if (categoryIndex < 0 || categoryIndex >= currentMap.categories.size())
	{
		return;
	}

	InputCategory& inputCategory = currentMap.categories[categoryIndex];

	ImGui::InputText("Name: ", inputCategory.name.data(), 32);
	ImGui::Spacing();
	ImGui::Text((std::to_string(inputCategory.configs.size()) + " Configs").c_str());
}

void InputMapViewer::DisplayConfigs()
{
	if (categoryIndex < 0 || categoryIndex >= currentMap.categories.size())
	{
		return;
	}

	InputCategory& inputCategory = currentMap.categories[categoryIndex];
	for (size_t i = 0; i < inputCategory.configs.size(); i++)
	{
		bool isSelected = configIndex == i;
		bool selected = ImGui::Selectable(inputCategory.configs[i].name.c_str(), &isSelected);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::Selectable("Delete"))
			{
				Experio::Algorithm::RemoveAt(inputCategory.configs, i);
			}
			ImGui::EndPopup();
		}

		if (selected && configIndex != i)
		{
			configIndex = i;
		}
	}

	if (ImGui::Button("+"))
	{
		inputCategory.configs.emplace_back("New Configs");
	}
}

void InputMapViewer::DisplayConfigInfo()
{
	if (categoryIndex < 0 && categoryIndex >= currentMap.categories.size())
	{
		return;
	}
	InputCategory& inputCategory = currentMap.categories[categoryIndex];

	if (configIndex < 0 && configIndex >= inputCategory.configs.size())
	{
		return;
	}
	InputConfig& inputConfig = inputCategory.configs[configIndex];

	ImGui::InputText("Name: ", inputConfig.name.data(), 32);
	LImGui::DisplayEnum<EInputType>(inputConfig.inputType, "Input Type");
	ImGui::Spacing();
	ImGui::Text((std::to_string(inputConfig.actions.size()) + " Actions").c_str());
	ImGui::Text((std::to_string(inputConfig.axes.size()) + " Axes").c_str());
}

void InputMapViewer::DisplayActionsAndAxes()
{
	if (categoryIndex < 0 || categoryIndex >= currentMap.categories.size())
	{
		return;
	}
	InputCategory& inputCategory = currentMap.categories[categoryIndex];

	if (configIndex < 0 || configIndex >= inputCategory.configs.size())
	{
		return;
	}
	InputConfig& inputConfig = inputCategory.configs[configIndex];

	ImGui::Spacing();
	DisplayActions();

	ImGui::Spacing();
	DisplayAxes();
}

void InputMapViewer::DisplayActions()
{
	InputConfig& inputConfig = currentMap.categories[categoryIndex].configs[configIndex];
	ImGui::Text("Actions: ");

	for (size_t i = 0; i < inputConfig.actions.size(); i++)
	{
		bool isSelected = actionIndex == i && action;
		bool selected = ImGui::Selectable(inputConfig.actions[i].name.c_str(), &isSelected);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::Selectable("Delete"))
			{
				Experio::Algorithm::RemoveAt(inputConfig.actions, i);
			}
			ImGui::EndPopup();
		}

		if (selected && (actionIndex != i || !action))
		{
			action = true;
			actionIndex = i;
		}
	}

	if (ImGui::Button("+ Action"))
	{
		inputConfig.actions.emplace_back("New Action");
	}
}

void InputMapViewer::DisplayAxes()
{
	InputConfig& inputConfig = currentMap.categories[categoryIndex].configs[configIndex];
	ImGui::Text("Axes: ");

	for (size_t i = 0; i < inputConfig.axes.size(); i++)
	{
		bool isSelected = actionIndex == i && !action;
		bool selected = ImGui::Selectable(inputConfig.axes[i].name.c_str(), &isSelected);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::Selectable("Delete"))
			{
				Experio::Algorithm::RemoveAt(inputConfig.axes, i);
			}
			ImGui::EndPopup();
		}

		if (selected && (actionIndex != i || action))
		{
			action = false;
			actionIndex = i;
		}
	}

	if (ImGui::Button("+ Axis"))
	{
		inputConfig.axes.emplace_back("New Axes");
	}
}

void InputMapViewer::DisplayActionAndAxis()
{
	if (action)
		DisplayAction();
	else
		DisplayAxis();
}

void InputMapViewer::DisplayAction()
{
	if (categoryIndex < 0 || categoryIndex >= currentMap.categories.size())
	{
		return;
	}
	InputCategory& inputCategory = currentMap.categories[categoryIndex];

	if (configIndex < 0 || configIndex >= inputCategory.configs.size())
	{
		return;
	}
	InputConfig& inputConfig = inputCategory.configs[configIndex];

	if (actionIndex < 0 || actionIndex >= inputConfig.actions.size())
	{
		return;
	}
	InputAction& inputAction = inputConfig.actions[actionIndex];
	
	ImGui::InputText("Name", inputAction.name.data(), inputAction.name.capacity());
	DisplayInputCode(inputConfig.inputType, inputAction.code);
}

void InputMapViewer::DisplayAxis()
{
	if (categoryIndex < 0 || categoryIndex >= currentMap.categories.size())
	{
		return;
	}
	InputCategory& inputCategory = currentMap.categories[categoryIndex];

	if (configIndex < 0 || configIndex >= inputCategory.configs.size())
	{
		return;
	}
	InputConfig& inputConfig = inputCategory.configs[configIndex];

	if (actionIndex < 0 || actionIndex >= inputConfig.axes.size())
	{
		return;
	}
	InputAxis& inputAxis = inputConfig.axes[actionIndex];

	for (uint32_t i = 0; i < inputAxis.axisPoints.Count(); i++)
	{
		ImGui::InputFloat("##X", &inputAxis.axisPoints[i].value);
		ImGui::SameLine();
		DisplayInputCode(inputConfig.inputType, inputAxis.axisPoints[i].code);
		ImGui::SameLine();
		if (ImGui::Button("-")) inputAxis.axisPoints.RemoveAt(i);
	}

	if (ImGui::Button("+"))
		inputAxis.axisPoints.EmplaceAppend();
}

void InputMapViewer::DisplayInputCode(EInputType inputType, InputCode& code)
{
	switch (inputType)
	{
	case EInputType::Gamepad: LImGui::DisplayEnum<EGamepadButton>(code.gamepadButton, "Button"); break;
	case EInputType::Keyboard: LImGui::DisplayEnum<EKeyCode>(code.keycode, "Keycode"); break;
	}
}

void InputMapViewer::SaveInputMap()
{
	std::ofstream outFile;
	outFile << "EXPERIO INPUT MAP" << std::endl;
	outFile << currentMap.NumCategories() << " " << currentMap.NumConfigs() << std::endl;
	outFile << std::endl;

	std::vector<InputCategory>& categories = currentMap.categories;
	for (size_t i = 0; i < categories.size(); i++)
	{
		SaveCategory(outFile, categories[i]);

		outFile << std::endl;
	}
}

void InputMapViewer::SaveCategory(std::ofstream& outFile, InputCategory& category)
{
	outFile << "CATEGORY " << category.name << std::endl;
	std::vector<InputConfig>& configs = category.configs;

	for (size_t i = 0; i < configs.size(); i++)
	{
		SaveConfig(outFile, configs[i]);
	}
}

void InputMapViewer::SaveConfig(std::ofstream& outFile, InputConfig& config)
{
	outFile << "CONFIG " << config.name << " "
		<< magic_enum::enum_name(config.inputType) << std::endl;

	std::vector<InputAction>& actions = config.actions;
	for (size_t i = 0; i < actions.size(); i++)
	{
		outFile << "ACTION " << actions[i].name << " ";
		switch (config.inputType)
		{
		case EInputType::Keyboard: outFile << magic_enum::enum_name(actions[i].code.keycode) << std::endl; break;
		case EInputType::Gamepad: outFile << magic_enum::enum_name(actions[i].code.gamepadButton) << std::endl; break;
		}
	}

	std::vector<InputAxis>& axes = config.axes;
	for (size_t i = 0; i < axes.size(); i++)
	{
		outFile << "AXIS " << axes[i].name << " " << axes[i].axisPoints.Count() << " ";
		for (size_t j = 0; j < axes[i].axisPoints.Count(); j++)
		{
			InputAxisPoint& axisPoint = axes[i].axisPoints[j];
			switch (config.inputType)
			{
			case EInputType::Keyboard: outFile << magic_enum::enum_name(axisPoint.code.keycode) << " "; break;
			case EInputType::Gamepad: outFile << magic_enum::enum_name(axisPoint.code.gamepadButton) << " "; break;
			}
			outFile << axisPoint.value << " ";
		}
		outFile << std::endl;
	}
}
