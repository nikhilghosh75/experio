#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include "Project.h"

extern size_t SizeOfComponent(unsigned int classId);

Component::Component(GameObject * object)
{
	gameObject = object;
	// TO-DO: Add IDs
}

Component::Component(GameObject * object, uint64_t id)
{
	gameObject = object;
	
	this->id = id;
}

Component * CopyComponent(GameObject * gameObject, Component * component, unsigned int classId)
{
	Component* newComponent = Project::componentManager->AddComponent(gameObject, classId);
	memcpy(newComponent, component, SizeOfComponent(classId));
	newComponent->gameObject = gameObject;
	newComponent->Start();
	return newComponent;
}
