#include "Component.h"
#include "GameObject.h"
#include "Scene.h"

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
