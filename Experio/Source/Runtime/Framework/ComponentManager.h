#pragma once
#include "Component.h"

/// <summary>
/// A class that manages components. It is implemented in the project.
/// You generally access it through Project->componentManager
/// </summary>

class ComponentManager
{
public:
	virtual void Start() {};

	virtual void Update() {};

	virtual void RenderScene() = 0;

	virtual Component* AddComponent(GameObject* gameObject, unsigned int id) = 0;

	virtual Component* GetComponent(GameObject* gameObject, unsigned int classId) = 0;

	virtual Component* GetComponentAtIndex(unsigned int classId, unsigned int index) = 0;

	virtual void DeleteComponent(GameObject* gameObject, unsigned int classId) = 0;

	virtual std::vector<unsigned int> GetComponentsIDsInGameObject(GameObject* gameObject) = 0;
	virtual std::vector<Component*> GetComponentsInGameObject(GameObject* gameObject) = 0;

	virtual void OnGameObjectDeleted(GameObject* gameObject) = 0;

	virtual unsigned int ComponentCount() const { return -1; }

	virtual std::vector<Component*> GetAllComponents() = 0;

	virtual void GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds) = 0;

	virtual void GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds, uint8_t sceneIndex) = 0;
};

#define PB_ADD_COMPONENT(_vectorName_) _vectorName_.emplace_back(gameObject);\
	_vectorName_.back().Start();\
	return (Component*)(&_vectorName_[_vectorName_.size() - 1]);

#define PB_GET_COMPONENT(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(_vectorName_[i].GetGameObject()->id == gameObject->id)\
		{\
			return (Component*)(&(_vectorName_[i]));\
		}\
	}\
	return nullptr;

#define PB_GET_COMPONENT_INDEX(_vectorName_) return (Component*)(&(_vectorName_[index]));

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

#define PB_UPDATE(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(!Scene::IsActive(_vectorName_[i].GetGameObject()) || _vectorName_[i].GetGameObject() == nullptr) { continue; }\
		_vectorName_[i].Update();\
	}\

#define PB_START(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
{\
	_vectorName_[i].Start();\
}\

#define PB_GET_COMPONENT_GAMEOBJECT(_classID_) component = GetComponent(gameObject, _classID_);\
	if(component != nullptr) returnVector.push_back(component);	

#define PB_GET_COMPONENT_IDS(_classID_) if(GetComponent(gameObject, _classID_) != nullptr) returnVector.push_back(_classID_);

#define PB_GET_ALL(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
{\
	vector.push_back(&_vectorName_[i]);\
}

#define PB_GET_ALL_IDS(_vectorName_, _id_) for(int i = 0; i < _vectorName_.size(); i++)\
{\
	components.push_back(&_vectorName_[i]);\
	componentIds.push_back(_id_);\
}

#define PB_GET_ALL_SCENE_IDS(_vectorName_, _id_) for(int i = 0; i < _vectorName_.size(); i++)\
{\
	if(_vectorName_[i].GetGameObject()->sceneIndex == sceneIndex)\
	{\
		components.push_back(&_vectorName_[i]); \
		componentIds.push_back(_id_); \
	}\
}