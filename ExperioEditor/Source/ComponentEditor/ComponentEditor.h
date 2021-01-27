#pragma once

#include "Runtime/Framework/Component.h"
#include "Runtime/Framework/Project.h"

class ComponentEditorBase
{
public:
	virtual void OnComponentAdd(Component* c) {};

	virtual void OnComponentOpen(Component* c) {};

	virtual void Display(Component* c) = 0;

	virtual void ContextMenu(Component* c) {}

	virtual unsigned int GetComponentID() const { return 0; }
};

template <typename T>
class ComponentEditor {};

#define COMPONENTEDITOR(_type_) public ComponentEditor<_type_>, public ComponentEditorBase

#define SETUP_COMPONENT_EDITOR(_type_) \
virtual unsigned int GetComponentID() const override { return Project::ClassTypeToInt<_type_>(); }
