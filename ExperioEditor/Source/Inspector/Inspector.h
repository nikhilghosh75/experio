#pragma once
#include "../Core/EditorModule.h"
#include "../ComponentEditor/ComponentEditor.h"
#include "Runtime/Framework/Framework.h"
#include <vector>

class GameObject;

class Inspector : public EditorModule
{
	// Vector of Component Editor
	std::vector<ComponentEditorBase*> componentEditors;

	bool locked;

	void DisplayGameObject(GameObject* object);

	void DisplaySceneSettings(GameObject* object);

	void DisplayMultipleGameObjects(std::vector<GameObject*>&);

	void DisplayMultipleTags(std::vector<GameObject*>&);
	void DisplayMultipleLayers(std::vector<GameObject*>&);

	void DisplayGameObjectInfo(GameObject* object);

	void DisplayTransform(GameObject* object);

	void DisplayRectTransform(GameObject* object);

	void UpdateComponents(std::vector<unsigned int> componentIDs, std::vector<Component*> components);

	void DisplayAddComponentMenu();

	void AddComponentToGameObjects(unsigned int componentId);
public:
	static Inspector* inspector;

	Inspector();

	~Inspector();

	virtual void Display() override;

	void Lock();

	void Unlock();
};