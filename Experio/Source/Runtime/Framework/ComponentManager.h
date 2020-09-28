#pragma once
#include "Component.h"
#include "Scene.h"
#include "../Debug/Debug.h"

class ComponentManager
{
public:
	virtual void Update() {};

	virtual Component* AddComponent(GameObject* gameObject, unsigned int id) { return nullptr; };

	virtual Component* GetComponent(GameObject* gameObject, unsigned int classId) { return nullptr; };

	virtual void DeleteComponent(GameObject* gameObject, unsigned int classId) {};

	virtual std::vector<unsigned int> GetComponentsIDsInGameObject(GameObject* gameObject) { return std::vector<unsigned int>(); };
	virtual std::vector<Component*> GetComponentsInGameObject(GameObject* gameObject) { return std::vector<Component*>(); };

	virtual unsigned int ComponentCount() { return -1; }
};

#define PB_ADD_COMPONENT(_vectorName_) _vectorName_.emplace_back(gameObject); return (Component*)(&_vectorName_[_vectorName_.size() - 1]);

#define PB_GET_COMPONENT(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(_vectorName_[i].GetGameObject() == gameObject)\
		{\
			return (Component*)(&(_vectorName_[i]));\
		}\
	}\
	return nullptr;

#define PB_DELETE_COMPONENT(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(gameObject == _vectorName_[i].GetGameObject())\
		{\
			foundComponent = true;\
		}\
		if(foundComponent)\
		{\
			if (i + 1 == _vectorName_.size())\
			{\
				_vectorName_.pop_back();\
				return;\
			}\
			_vectorName_[i] = _vectorName_[i + 1];\
		}\
	}\
	break;\

#define PB_UPDATE(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(!Scene::IsActive(_vectorName_[i].GetGameObject())) { continue; }\
		_vectorName_[i].Update();\
	}\

/**/