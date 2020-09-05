#pragma once
#include "GameObject.h"
#include <string>
#include <fstream>

class PrefabLoader
{
public:
	static GameObject* LoadPrefab(std::string fileName, GameObject* parent);
	static GameObject* LoadPrefab(std::string fileName, GameObject* parent, 
		FVector3 localPosition);
	static GameObject* LoadPrefab(std::string fileName, GameObject* parent, 
		FVector3 localPosition, FQuaternion localRotation);

private:
	static void AddComponentsToObject(std::ifstream& stream, GameObject* gameObject);
};