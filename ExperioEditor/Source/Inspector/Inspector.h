#pragma once
#include "../Core/EditorModule.h"
#include "../ComponentEditor/ComponentEditor.h"
#include <vector>

class GameObject;

class Inspector : public EditorModule
{
	// Vector of Component Editor
	std::vector<ComponentEditorBase*> componentEditors;

	void DisplayGameObject(uint64_t id);

	void DisplayGameObjectInfo(GameObject* object);

	void DisplayTransform(GameObject* object);

	void UpdateComponents(std::vector<unsigned int> componentIDs);
public:
	Inspector();

	~Inspector();

	virtual void Display() override;
};