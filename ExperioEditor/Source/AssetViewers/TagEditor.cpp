#include <sstream>
#include "TagEditor.h"
#include "../Framework/Values.h"
#include "Runtime/Containers/Algorithm.h"

TagEditor* TagEditor::tagEditor;

void TagEditor::OnValuesChanged()
{
	tagEditor->tags = ExperioEditor::GetTags().GetPairs();
}

TagEditor::TagEditor()
{
	this->name = "Tag Editor";
	this->category = EEditorModuleCategory::Viewer;
	
	this->tags = ExperioEditor::GetTags().GetPairs();
	tagEditor = this;
	ExperioEditor::AddEventToOnValuesChanged(OnValuesChanged);
}

void TagEditor::Display()
{
	ImGui::Text("Tags");

	std::stringstream ss;
	unsigned int size = ExperioEditor::GetTags().GetSize();
	ss << size << "/" << "65,535";
	ImGui::Text(ss.str().c_str());

	for (uint16_t i = 0; i < this->tags.size(); i++)
	{
		bool changed = ImGui::InputText(std::to_string(tags[i].first).c_str(), tags[i].second.data(), tags[i].second.capacity());
		if (changed)
		{
			if (tags[i].second.size() != 0)
			{
				ExperioEditor::SetValueName(tags[i].first, tags[i].second, EValueType::Tag);
			}
		}

		ImGui::SameLine();
		ImGui::PushID(i);
		if (ImGui::Button("-"))
		{
			ExperioEditor::DeleteValue(tags[i].first, EValueType::Tag);
			Experio::Algorithm::RemoveAt(this->tags, i);
		}
		ImGui::PopID();
	}

	if (size < 65535)
	{
		if (ImGui::Button("Add Tag"))
		{
			this->tags.emplace_back(ExperioEditor::GetNextAvailibleValue(EValueType::Tag), "Tag");
			this->tags[this->tags.size() - 1].second.reserve(32);
			ExperioEditor::AddValue(EValueType::Tag);
		}
	}
}
