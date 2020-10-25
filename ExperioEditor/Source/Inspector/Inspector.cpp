#include "Inspector.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "Runtime/Framework/Framework.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "../Framework/EditorProject.h"

Inspector::Inspector()
{
	this->category = EEditorModuleCategory::Core;
	this->name = "Inspector";
}

void Inspector::Display()
{
	std::vector<GameObject> objects = SceneHierarchy::hierarchy->GetSelectedItems();

	if (objects.size() == 1)
	{
		GameObject* object = Scene::FindGameObjectFromId(objects[0].id);
		FVector3 position = object->localPosition;
		FQuaternion rotation = object->localRotation;
		FVector3 scale = object->localScale;

		LImGui::DisplayTransform(position, rotation, scale);

		object->localPosition = position;
		object->localRotation = rotation;
		object->localScale = scale;

		std::vector<unsigned int> components = Project::componentManager->GetComponentsIDsInGameObject(object);
		for (int i = 0; i < components.size(); i++)
		{
			std::string componentName = EditorProject::classes.Get(components[i]);
			ImGui::Text(componentName.c_str());
		}
	}
}
