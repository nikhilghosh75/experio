#pragma once
#include "Component.h"
#include "../Debug/GDebug.h"

class ComponentManager
{
public:
	virtual void Update() {};

	virtual void AddComponent(GameObject* gameObject, unsigned int id);

	virtual Component* GetComponent(GameObject* gameObject, unsigned int classId);

	virtual void DeleteComponent(GameObject* gameObject, unsigned int classId);
};

class TestComponentManager : ComponentManager
{
public:
	std::vector<TestComponent> testComponentInstances;

	virtual void Update() override 
	{
		for (int i = 0; i < testComponentInstances.size(); i++)
		{
			testComponentInstances[i].Update();
		}
	}

	virtual void AddComponent(GameObject* gameObject, unsigned int classId) override
	{
		switch (classId)
		{
		case 2:
			testComponentInstances.emplace_back(gameObject);
			break;
		}
		GDebug::LogError("Component cannot be found. Make sure to regenerate the project");
	}

	virtual Component* GetComponent(GameObject* gameObject, unsigned int classId) override
	{
		switch (classId)
		{
		case 2:
			for (int i = 0; i < testComponentInstances.size(); i++)
			{
				if (testComponentInstances[i].GetGameObject() == gameObject)
				{
					return (Component*)(&(testComponentInstances[i]));
				}
			}
			return nullptr;
		}

		GDebug::LogError("Component cannot be found. Make sure to regenerate the project");
		return nullptr;
	}

	virtual void DeleteComponent(GameObject* gameObject, unsigned int classId) override
	{
		bool foundComponent = false;
		switch (classId)
		{
		case 2:
			for (int i = 0; i < testComponentInstances.size(); i++)
			{
				if (gameObject == testComponentInstances[i].GetGameObject())
				{
					foundComponent = true;
				}
				if (foundComponent)
				{
					if (i + 1 == testComponentInstances.size())
					{
						testComponentInstances.pop_back();
						return;
					}
					testComponentInstances[i] = testComponentInstances[i + 1];
				}
			}
			break;
		}
	}
};