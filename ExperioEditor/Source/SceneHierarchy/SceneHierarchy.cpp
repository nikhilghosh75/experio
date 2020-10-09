#include "SceneHierarchy.h"
#include "Runtime/Framework/GameObject.h"
#include "Runtime/Rendering/LImGui.h"
#include "Runtime/Framework/Scene.h"

SceneHierarchy::SceneHierarchy()
{
	this->category = EEditorModuleCategory::Core;
	this->name = "Scene Hierarchy";
}

void SceneHierarchy::Display()
{
	std::string& selectedItem = this->currentlySelectedItem;

	Scene::ForAllActiveScenes([&selectedItem](Scene scene) {
		TTypedTree<GameObject>* hierarchy = GameObject::MakeTree(scene.GetId());
		TTypedTree<std::string>* hierarchyNames = new TTypedTree<std::string>();
		MakeTreeFromBase<GameObject, std::string>(hierarchy, hierarchyNames, [](GameObject object) { return object.name; });
		LImGui::DisplayTree(hierarchyNames, scene.GetName(), selectedItem);
		
		if (selectedItem.size() == 0) return;

		TTypedTreeNode<GameObject>* selectedObjectNode = SearchCorrespondingTrees<std::string, GameObject>
			(hierarchyNames, hierarchy, [&selectedItem](std::string str) { return str == selectedItem; });

		if (selectedObjectNode != nullptr)
		{
			Debug::Log(selectedObjectNode->object.name);
		}

		delete hierarchy;
		delete hierarchyNames;
	});
}
