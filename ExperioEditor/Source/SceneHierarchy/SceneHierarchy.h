#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Framework/GameObject.h"

class SceneHierarchy : public EditorModule
{
	std::vector<GameObject*> currentlySelectedItems;

	static void HandleDragDrop(const GameObject* gameObject);
	static void HandleSwap(uint64_t fromID, uint64_t toID);

	static void HandleContextMenu(GameObject* gameObject);

	bool locked;

public:
	static SceneHierarchy* hierarchy;

	static void DisplayGameObjectTree(GameObject* gameObject, std::vector<GameObject*>& selectedItems);

	SceneHierarchy();

	virtual void Display() override;

	// Dont make this const
	std::vector<GameObject*>& GetSelectedItems();

	void Lock();

	void Unlock();
};