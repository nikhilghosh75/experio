#include "LayerEditor.h"
#include <sstream>
#include "../Framework/Values.h"
#include "Runtime/Containers/Algorithm.h"

LayerEditor::LayerEditor()
{
	this->name = "Layer Editor";
	this->category = EEditorModuleCategory::Viewer;

	this->layers = ExperioEditor::GetLayers().GetPairs();
}

void LayerEditor::Display()
{
	ImGui::Text("Layers");

	std::stringstream ss;
	unsigned int size = ExperioEditor::GetTags().GetSize();
	ss << size << "/" << "64";
	ImGui::Text(ss.str().c_str());

	for (uint16_t i = 0; i < this->layers.size(); i++)
	{
		bool changed = ImGui::InputText(std::to_string(layers[i].first).c_str(), layers[i].second.data(), layers[i].second.capacity());
		if (changed)
		{
			if (layers[i].second.size() != 0)
			{
				ExperioEditor::SetValueName(layers[i].first, layers[i].second, EValueType::Layer);
			}
		}

		ImGui::SameLine();
		ImGui::PushID(i);
		if (ImGui::Button("-"))
		{
			ExperioEditor::DeleteValue(layers[i].first, EValueType::Layer);
			Experio::Algorithm::RemoveAt(this->layers, i);
		}
		ImGui::PopID();
	}

	if (size < 64)
	{
		if (ImGui::Button("Add Layer"))
		{
			this->layers.emplace_back(ExperioEditor::GetNextAvailibleValue(EValueType::Layer), "Layer");
			this->layers[this->layers.size() - 1].second.reserve(32);
			ExperioEditor::AddValue(EValueType::Layer);
		}
	}
}
