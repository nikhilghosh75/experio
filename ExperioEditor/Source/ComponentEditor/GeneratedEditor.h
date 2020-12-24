#pragma once
#include "ComponentEditor.h"
#include "../BuildSystem/SerializationInfo.h"

class GeneratedEditor : public ComponentEditorBase
{
	unsigned int classId;
	Component* component;

	std::vector<FSerializationInfo> serializedFields;

public:
	GeneratedEditor();

	GeneratedEditor(unsigned int classId);

	GeneratedEditor(unsigned int classId, Component* component);

	virtual unsigned int GetComponentID() const override { return this->classId; }

	virtual void Display(Component* component) override;

private:
	void GenerateSerializedFields();

	void DisplayParamType(FSerializationInfo& serializedField, Component* component);
};