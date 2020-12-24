#include "Inspector.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Framework/Framework.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "../Framework/EditorProject.h"
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
	
	DisplayGameObjectInfo(object);
	DisplayTransform(object);

	std::vector<unsigned int> componentIDs = Project::componentManager->GetComponentsIDsInGameObject(object);
	std::vector<Component*> components = Project::componentManager->GetComponentsInGameObject(object);
	UpdateComponents(componentIDs, components);

	for (int i = 0; i < componentEditors.size(); i++)
	{
		if (ImGui::TreeNode(EditorProject::componentClasses.Get(componentIDs[i]).name.c_str()))
		{
			componentEditors[i]->Display(components[i]);
			ImGui::TreePop();
		}
	}
}

void Inspector::DisplayGameObjectInfo(GameObject * object)
{
	bool changed = ImGui::InputText("##Name", object->name.data(), 32);
	if (changed)
	{
		// Add stuff
	}

	LImGui::DisplayTag(object->tag, ExperioEditor::GetTags());
	LImGui::DisplayLayer(object->layer, ExperioEditor::GetLayers());
}

void Inspector::DisplayTransform(GameObject * object)
{
	if (ImGui::TreeNode("Transform"))
	{
		FVector3 position = object->localPosition;
		FQuaternion rotation = object->localRotation;
		FVector3 scale = object->localScale;

		LImGui::DisplayTransform(position, rotation, scale);

		object->localPosition = position;
		object->localRotation = rotation;
		object->localScale = scale;

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
				// componentEditors.push_back(new VirtualCameraEditor()); break;
			case 101:
				InsertAt(componentEditors, (ComponentEditorBase*)(new MeshEditor()), i);
				break;
				// componentEditors.push_back(new MeshEditor()); break;
			case 103:
				InsertAt(componentEditors, (ComponentEditorBase*)(new BillboardEditor()), i);
				// componentEditors.push_back(new BillboardEditor()); break;
			default:
				InsertAt(componentEditors, (ComponentEditorBase*)(new GeneratedEditor(componentIDs[i], components[i])), i);
				break;
				// componentEditors.push_back(new GeneratedEditor(componentIDs[i], components[i])); break;
			}
		}
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
