#include "SceneHierarchy.h"
#include "Runtime/Framework/GameObject.h"
#include "Runtime/Rendering/LImGui.h"
#include "Runtime/Framework/Scene.h"
#include "Runtime/Containers/LStandard.h"

void SceneHierarchy::HandleDragDrop(const GameObject * gameObject)
{
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		uint64_t id = gameObject->id;
		ImGui::SetDragDropPayload("EXPERIO_GAME_OBJECT", &id, sizeof(uint64_t));
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_GAME_OBJECT");
		if (payload != nullptr)
		{
			uint64_t id = *(const uint64_t*)payload->Data;
			HandleSwap(id, gameObject->id);
		}
		Debug::Log("Payload not accepted");
		ImGui::EndDragDropTarget();
	}
}

void SceneHierarchy::HandleSwap(uint64_t fromID, uint64_t toID)
{
	// Debug::log << "Swap " << fromID << ", " << toID << Debug::endl;
	if (fromID == toID)
	{
		return;
	}

	GameObject* fromObject = Scene::FindGameObjectFromId(fromID);
	GameObject* toObject = Scene::FindGameObjectFromId(toID);

	// Same Parent
	if (fromObject->parent->id == toObject->parent->id)
	{
		GameObject* parentObject = fromObject->parent;
		unsigned int fromIndex, toIndex;
		for (unsigned int i = 0; i < parentObject->children.size(); i++)
		{
			if (parentObject->children[i]->id == fromID)
			{
				fromIndex = i;
			}
			if (parentObject->children[i]->id == toID)
			{
				toIndex = i;
			}
		}

		// Swap
		parentObject->children[fromIndex] = toObject;
		parentObject->children[toIndex] = fromObject;
	}

	// TO-DO: Add other types here
}

void SceneHierarchy::DisplayGameObjectTree(const GameObject * gameObject, std::vector<GameObject>& selectedItems)
{
	bool isSelected = LStandard::ExistsInVector(selectedItems, *gameObject);
	if (gameObject->children.size() == 0)
	{
		if (ImGui::Selectable(gameObject->name.c_str(), isSelected))
		{
			if (!isSelected)
			{
				selectedItems.push_back(*gameObject);
			}
			else
			{
				LStandard::RemoveElement(selectedItems, *gameObject);
			}
		}
		HandleDragDrop(gameObject);
	}
	else
	{
		ImGuiTreeNodeFlags_ flags = isSelected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
		if (ImGui::TreeNodeEx(gameObject->name.c_str(), flags))
		{
			if (ImGui::IsItemClicked())
			{
				if (isSelected)
				{
					LStandard::RemoveElement(selectedItems, *gameObject);
				}
				else
				{
					selectedItems.push_back(*gameObject);
				}
			}

			HandleDragDrop(gameObject);

			for (int i = 0; i < gameObject->children.size(); i++)
			{
				DisplayGameObjectTree(gameObject->children[i], selectedItems);
			}
			ImGui::TreePop();
		}
	}
}

SceneHierarchy::SceneHierarchy()
{
	this->category = EEditorModuleCategory::Core;
	this->name = "Scene Hierarchy";
}

void SceneHierarchy::Display()
{
	std::vector<GameObject>& selectedItems = this->currentlySelectedItems;

	Scene::ForAllActiveScenes([&selectedItems](Scene scene) {
		SceneHierarchy::DisplayGameObjectTree(&scene.sceneRoot, selectedItems);
	});
}
