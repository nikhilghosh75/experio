#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Framework/GameObject.h"

class SceneHierarchy : public EditorModule
{
	std::vector<GameObject> currentlySelectedItems;

	static void HandleDragDrop(const GameObject* gameObject);
	static void HandleSwap(uint64_t fromID, uint64_t toID);

public:
	static SceneHierarchy* hierarchy;

	static void DisplayGameObjectTree(const GameObject* gameObject, std::vector<GameObject>& selectedItems);

	SceneHierarchy();

	virtual void Display() override;

	const std::vector<GameObject>& GetSelectedItems() const;
};