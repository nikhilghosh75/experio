#pragma once
#include "Component.h"
#include "GameObject.h"

template<class T>
class System
{
public:
	virtual void Start() = 0;

	virtual T* AddComponent(GameObject* gameObject) = 0;

	virtual T* GetComponent(GameObject* gameObject) = 0;

	virtual void DeleteComponent(GameObject* gameObject) = 0;

	void OnGameObjectDeleted(GameObject* gameObject)
	{
		DeleteComponent(gameObject);
	}

	virtual void GetAll(std::vector<Component*>& components) = 0;

	virtual void GetAllOfScene(std::vector<Component*>& components, uint8_t sceneId) = 0;

	virtual void Update() = 0;

	virtual unsigned int Size() const = 0;
	
	virtual unsigned int NumInScene(uint8_t sceneId) const = 0;
};

#define SETUP_SYSTEM(_className_, _componentName_) \
	static _className_* instance;\
	\
	_className_() { instance = this; }\
	\
	static _className_* Get() { return instance; }

#define SETUP_SYSTEM_CPP(_className_, _componentName_) \
	_className_* _className_::instance;