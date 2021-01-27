#include "Inspector.h"
#include "InspectorUndo.h"
#include "Runtime/Containers/Algorithm.h"
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

using namespace Experio::Algorithm;

GeneratedEditor generatedEditor;

void Inspector::DisplayGameObject(uint64_t id)
{
	GameObject* object = Scene::FindGameObjectFromId(id);
	if (object == nullptr) return;
	
	DisplayGameObjectInfo(object);
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
		if (ImGui::BeginMenu("Rendering"))
		{
			if (ImGui::MenuItem("Virtual Camera"))
				AddComponentToGameObjects(100);
			if (ImGui::MenuItem("Mesh"))
				AddComponentToGameObjects(101);
			if (ImGui::MenuItem("Particle System"))
				AddComponentToGameObjects(102);
			if (ImGui::MenuItem("Billboard"))
				AddComponentToGameObjects(103);
			
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("UI"))
		{
			if (ImGui::MenuItem("Text Component"))
				AddComponentToGameObjects(104);

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Custom"))
		{
			if (ImGui::MenuItem("Spaceship"))
				AddComponentToGameObjects(1024);

			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
}

void Inspector::AddComponentToGameObjects(unsigned int componentId)
{
	std::vector<GameObject> objects = SceneHierarchy::hierarchy->GetSelectedItems();
	if (objects.size() == 0) return;

	GameObject* object = Scene::FindGameObjectFromId(objects[0].id);
	object->AddComponentByComponentID(componentId);
	UndoSystem::AddCommand(new AddComponentCommand(object, componentId));
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
	std::vector<GameObject> objects = SceneHierarchy::hierarchy->GetSelectedItems();

	if (objects.size() == 1)
	{
		DisplayGameObject(objects[0].id);
	}

	DisplayAddComponentMenu();
}
