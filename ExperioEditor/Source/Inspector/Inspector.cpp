#include "Inspector.h"
#include "InspectorUndo.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Debug/Profiler.h"
#include "Runtime/Framework/Framework.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "../Framework/EditorProject.h"
#include "../Framework/UndoSystem.h"
#include "../Framework/Values.h"
#include "../ComponentEditor/GeneratedEditor.h"
#include "../ComponentEditor/Renderable/MeshComponentEditor.h"
#include "../ComponentEditor/Renderable/BillboardComponentEditor.h"
#include "../ComponentEditor/Renderable/VirtualCameraEditor.h"
#include "../ComponentEditor/UI/TextComponentEditor.h"

using namespace Experio::Algorithm;

GeneratedEditor generatedEditor;

void Inspector::DisplayGameObject(GameObject* object)
{
	if (object == nullptr) return;
	
	DisplayGameObjectInfo(object);

	if (object->isUI)
		DisplayRectTransform(object);
	else
		DisplayTransform(object);

	std::vector<unsigned int> componentIDs = Project::componentManager->GetComponentsIDsInGameObject(object);
	std::vector<Component*> components = Project::componentManager->GetComponentsInGameObject(object);
	UpdateComponents(componentIDs, components);

	for (int i = 0; i < componentEditors.size(); i++)
	{
		if (ImGui::TreeNode(EditorProject::componentClasses.Get(componentIDs[i]).name.c_str()))
		{
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::Selectable("Delete"))
				{
					object->DeleteComponentByComponentID(componentIDs[i]);
					UndoSystem::AddCommand(new AddComponentCommand(object, componentIDs[i], false));
					ImGui::EndPopup(); ImGui::TreePop();
					break;
				}
				componentEditors[i]->ContextMenu(components[i]);
				ImGui::EndPopup();
			}
			componentEditors[i]->Display(components[i]);
			ImGui::TreePop();
		}
	}
}

void Inspector::DisplayMultipleGameObjects(std::vector<GameObject*>& gameObjects)
{
	ImGui::Text("Name: "); ImGui::SameLine(); ImGui::Text("Multiple");

	DisplayMultipleTags(gameObjects);
	DisplayMultipleLayers(gameObjects);
}

void Inspector::DisplayMultipleTags(std::vector<GameObject*>& gameObjects)
{
	uint16_t tag = gameObjects[0]->tag;
	for (size_t i = 1; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->tag != tag)
		{
			tag = ExperioEditor::NumValues(EValueType::Tag);
			break;
		}
	}

	uint16_t lastTag = tag;
	LImGui::DisplayTag(tag, ExperioEditor::GetTags());
	if (lastTag != tag)
	{
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->tag = tag;
		}
	}
}

void Inspector::DisplayMultipleLayers(std::vector<GameObject*>& gameObjects)
{
	uint8_t layer = gameObjects[0]->layer;
	for (size_t i = 1; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->layer != layer)
		{
			layer = ExperioEditor::NumValues(EValueType::Layer);
			break;
		}
	}

	uint8_t lastLayer = layer;
	LImGui::DisplayLayer(layer, ExperioEditor::GetLayers());
	if (lastLayer != layer)
	{
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->layer = layer;
		}
	}
}

void Inspector::DisplayGameObjectInfo(GameObject * object)
{
	std::string oldName = object->name;
	bool changed = ImGui::InputText("##Name", object->name.data(), 32);
	if (changed)
	{
		UndoSystem::AddCommand(new SetNameCommand(object, oldName, object->name));
	}

	uint16_t lastTag = object->tag;
	LImGui::DisplayTag(object->tag, ExperioEditor::GetTags());
	if (lastTag != object->tag)
	{
		UndoSystem::AddCommand(new SetTagCommand(object, lastTag, object->tag));
	}

	uint8_t lastLayer = object->layer;
	LImGui::DisplayLayer(object->layer, ExperioEditor::GetLayers());
	if (lastLayer != object->layer)
	{
		UndoSystem::AddCommand(new SetLayerCommand(object, lastLayer, object->layer));
	}

	ImGui::Checkbox("UI: ", &object->isUI);
}

void Inspector::DisplayTransform(GameObject * object)
{
	if (ImGui::TreeNode("Transform"))
	{
		FVector3 position = object->localPosition;
		FQuaternion rotation = object->localRotation;
		FVector3 scale = object->localScale;

		LImGui::DisplayTransform(position, rotation, scale);

		if (position != object->localPosition)
		{
			UndoSystem::AddCommand(new MoveCommand(object, position - object->localPosition));
			object->localPosition = position;
		}

		if (rotation != object->localRotation)
		{
			UndoSystem::AddCommand(new RotateCommand(object, rotation / object->localRotation));
			object->localRotation = rotation;
		}

		if (scale != object->localScale)
		{
			UndoSystem::AddCommand(new ScaleCommand(object, scale / object->localScale));
			object->localScale = scale;
		}

		ImGui::TreePop();
	}
}

void Inspector::DisplayRectTransform(GameObject* object)
{
	if (ImGui::TreeNode("RectTransform"))
	{
		LImGui::DisplayEnum<EPositionConstraintType>(object->rectTransform.xConstraint.type, "X:");
		ImGui::SameLine();
		ImGui::InputFloat("Offset:", &object->rectTransform.xConstraint.value);

		LImGui::DisplayEnum<EPositionConstraintType>(object->rectTransform.yConstraint.type, "Y:");
		ImGui::SameLine();
		ImGui::InputFloat("Offset:", &object->rectTransform.yConstraint.value);

		LImGui::DisplayEnum<EDimensionConstraintType>(object->rectTransform.widthConstraint.type, "Width:");
		ImGui::SameLine();
		ImGui::InputFloat("Width:", &object->rectTransform.widthConstraint.value);

		LImGui::DisplayEnum<EDimensionConstraintType>(object->rectTransform.heightConstraint.type, "Height:");
		ImGui::SameLine();
		ImGui::InputFloat("Height:", &object->rectTransform.heightConstraint.value);

		ImGui::TreePop();
	}
}

void Inspector::UpdateComponents(std::vector<unsigned int> componentIDs, std::vector<Component*> components)
{
	// Delete Components
	for (int i = 0; i < componentEditors.size(); i++)
	{
		bool found = false;
		unsigned int editorClassID = componentEditors[i]->GetComponentID();

		for (int j = 0; j < componentIDs.size(); j++)
		{
			if (componentIDs[j] == editorClassID)
			{
				found = true; break;
			}
		}

		if (!found)
		{
			delete componentEditors[i];
			for (int j = i; j < componentEditors.size() - 1; j++)
			{
				componentEditors[j] = componentEditors[j + 1];
			}
			componentEditors.pop_back();
		}
	}

	// Add Components
	for (int i = 0; i < componentIDs.size(); i++)
	{
		bool found = false;
		
		for (int j = 0; j < componentEditors.size(); j++)
		{
			if (componentEditors[j]->GetComponentID() == componentIDs[i])
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			switch (componentIDs[i])
			{
			case 100:
				InsertAt(componentEditors, (ComponentEditorBase*)(new VirtualCameraEditor()), i);
				break;
			case 101:
				InsertAt(componentEditors, (ComponentEditorBase*)(new MeshEditor()), i);
				break;
			case 103:
				InsertAt(componentEditors, (ComponentEditorBase*)(new BillboardEditor()), i); 
				break;
			case 104:
				InsertAt(componentEditors, (ComponentEditorBase*)(new TextComponentEditor()), i);
				break;
			default:
				InsertAt(componentEditors, (ComponentEditorBase*)(new GeneratedEditor(componentIDs[i], components[i])), i);
				break;
			}
		}
	}

	if (componentEditors.size() > componentIDs.size())
	{
		componentEditors.pop_back();
	}
}

// Move this later
void Inspector::DisplayAddComponentMenu()
{
	if (ImGui::Button("+"))
	{
		ImGui::OpenPopup("##AddComponent");
	}

	if (ImGui::BeginPopup("##AddComponent"))
	{
		EditorProject::componentCategories.ForEach([this](unsigned int& id) {
			if (ImGui::MenuItem(EditorProject::componentClasses.Get(id).name.c_str()))
				AddComponentToGameObjects(id);
		}, [](const std::string& str) {
			if (str.empty())
				return true;
			return (bool)ImGui::BeginMenu(str.c_str());
		}, [](const std::string& str){
			if (str.empty())
				return;
			ImGui::EndMenu();
		});
		ImGui::EndPopup();
	}
}

void Inspector::AddComponentToGameObjects(unsigned int componentId)
{
	std::vector<GameObject*>& objects = SceneHierarchy::hierarchy->GetSelectedItems();
	if (objects.size() == 0) return;

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->AddComponentByComponentID(componentId);
		UndoSystem::AddCommand(new AddComponentCommand(objects[i], componentId));
	}
}

Inspector::Inspector()
{
	this->category = EEditorModuleCategory::Core;
	this->name = "Inspector";
}

Inspector::~Inspector()
{
	for (int i = 0; i < componentEditors.size(); i++)
	{
		delete componentEditors[i];
	}
}

void Inspector::Display()
{
	PROFILE_SCOPE("Inspector::Display");

	std::vector<GameObject*>& objects = SceneHierarchy::hierarchy->GetSelectedItems();

	if (objects.size() == 0)
	{
		ImGui::Text("Select a GameObject to view its info");
	}
	else if (objects.size() == 1)
	{
		DisplayGameObject(objects[0]);
		DisplayAddComponentMenu();
	}
	else
	{
		DisplayMultipleGameObjects(objects);
		DisplayAddComponentMenu();
	}
}
