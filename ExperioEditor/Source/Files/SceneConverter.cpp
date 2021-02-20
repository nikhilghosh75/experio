#include "SceneConverter.h"
#include "../BuildSystem/AssetMapSaver.h"
#include "../BuildSystem/LSerializationOperations.h"
#include "../CodeParser/CodeProject.h"
#include "../Framework/EditorProject.h"
#include "Runtime/Containers/THashtable.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Framework/Scene.h"
#include "Runtime/Framework/SceneLoader.h"
#include "Runtime/Containers/LString.h"
#include <filesystem>

const uint32_t sizeOfGameObject = 88;

#define PB_HEADER_LENGTH 68

extern void SaveBinaryComponentToScene(unsigned int componentID, Component* component, std::ofstream& stream);

extern size_t SerializedSizeOfComponent(unsigned int classId);

extern std::vector<std::string> GetParamsList(unsigned int classId);

void SceneConverter::LegacyConvertSceneToBinary(const std::string & fromFilepath, const std::string & toFilepath)
{
	if (!LFileOperations::DoesFileHaveExtension(fromFilepath, ".pbscene"))
	{
		Debug::LogError("From Filepath is not a correct filepath");
		return;
	}

	if (!LFileOperations::DoesFileHaveExtension(toFilepath, ".pbbscene"))
	{
		Debug::LogError("To Filepath is not a correct filepath");
		return;
	}

	SceneLoader::LoadSceneFromFile(fromFilepath, MAX_SCENES - 3);
	Scene& currentScene = Scene::scenes[MAX_SCENES - 3];

	std::ofstream outFile(toFilepath, std::ios::out | std::ios::binary);

	outFile.write("PBBSCENE", 8);
	outFile.write("0000", 4); // Bytes 8-11

	uint32_t sizeOfGameObjects = 0;
	ForEach(&currentScene.sceneRoot, [&sizeOfGameObjects](GameObject* object) {
		sizeOfGameObjects += sizeOfGameObject + object->name.size();
	});

	uint32_t gameObjectOffset = 68;
	uint32_t componentsOffset = gameObjectOffset + sizeOfGameObjects;
	uint32_t sceneDataAssetID = AssetMapSaver::NextAssetMapIndex();
	uint32_t numComponents = currentScene.GetNumComponents();
	uint32_t numGameObjects = currentScene.GetNumGameObjects();

	outFile.write((char*)&gameObjectOffset, 4);
	outFile.write((char*)&componentsOffset, 4);
	outFile.write((char*)&sceneDataAssetID, 4);
	outFile.write("0000", 4);
	outFile.write((char*)&numComponents, 4);
	outFile.write((char*)&numGameObjects, 4);
	
	outFile.write(currentScene.GetName().c_str(), 32);

	THashtable<GameObject*, uint32_t, PointerHashFunction<GameObject>> indexes;
	uint32_t gameObjectindex = 0;

	// Serialize Game Objects
	ForEach(&currentScene.sceneRoot, 
	[&outFile, &indexes, &gameObjectindex](GameObject* gameObject) 
	{
		uint8_t nameLength = gameObject->name.size();
		uint8_t layer = gameObject->layer;
		uint16_t tag = gameObject->tag;
		uint32_t parentIndex = 0;
		if (gameObject->parent != nullptr)
		{
			parentIndex = indexes.Get(gameObject->parent);
		}
		uint8_t numChildren = gameObject->children.size();
		bool isActive = gameObject->isActive;
		FVector3 position = gameObject->localPosition;
		FQuaternion rotation = gameObject->localRotation;
		FVector3 scale = gameObject->localScale;
		uint32_t id = gameObjectindex;

		outFile.write((char*)&nameLength, 1);
		outFile.write((char*)&layer, 1);
		outFile.write((char*)&tag, 2);
		outFile.write((char*)&parentIndex, 4);
		outFile.write((char*)&numChildren, 1);
		outFile.write((char*)&isActive, 1);
		outFile.write("00", 2);
		outFile.write((char*)&position, 12);
		outFile.write((char*)&rotation, 16);
		outFile.write((char*)&scale, 12);
		outFile.write((char*)&id, 4);

		outFile.write(gameObject->name.c_str(), nameLength);

		indexes.Insert(gameObject, gameObjectindex);
		gameObjectindex++;
	});

	std::vector<Component*> components;
	std::vector<unsigned int> componentIds;

	Project::componentManager->GetAllComponents(components, componentIds, MAX_SCENES - 3);
	for (size_t i = 0; i < components.size(); i++)
	{
		outFile.write((char*)&(componentIds[i]), 4);

		uint32_t indexOfGameObject = indexes.Get(components[i]->GetGameObject());
		outFile.write((char*)&(indexOfGameObject), 4);

		uint16_t paramAmount = GetParamsList(componentIds[i]).size();
		outFile.write((char*)&(paramAmount), 2);

		uint16_t componentSize = SerializedSizeOfComponent(componentIds[i]);
		outFile.write((char*)&(componentSize), 2);

		SaveBinaryComponentToScene(componentIds[i], components[i], outFile);
	}

	outFile.close();
	Scene::UnloadScene(MAX_SCENES - 3);
}

void SceneConverter::ConvertSceneToBinary(const std::string & fromFilepath, const std::string & toFilepath)
{
	if (!LFileOperations::DoesFileHaveExtension(fromFilepath, ".pbscene"))
	{
		Debug::LogError("From Filepath is not a correct filepath");
		return;
	}

	if (!LFileOperations::DoesFileHaveExtension(toFilepath, ".pbbscene"))
	{
		Debug::LogError("To Filepath is not a correct filepath");
		return;
	}

	std::ifstream inFile(fromFilepath);
	FileBuffer buffer = LFileOperations::ReadFileToBuffer(inFile);

	std::ofstream outFile(toFilepath, std::ios::out | std::ios::binary);

	GenerateHeader(buffer, outFile);
	GenerateGameObject(buffer, outFile);
	GenerateComponent(buffer, outFile);
}

size_t SceneConverter::SerializedSizeOfScene(const std::string & filepath)
{
	if (LFileOperations::DoesFileHaveExtension(filepath, ".pbbscene"))
	{
		return std::filesystem::file_size(filepath);
	}
	
	size_t sizeOf = 0;
	std::ifstream inFile(filepath);
	FileBuffer buffer = LFileOperations::ReadFileToBuffer(inFile);

	// Fix this later
	sizeOf = PB_HEADER_LENGTH + GetNumGameObjects(buffer) * sizeOfGameObject + GetNumComponents(buffer) * (12 + 8);
	return sizeOf;
}

void SceneConverter::GenerateHeader(const FileBuffer & buffer, std::ofstream & outFile)
{
	outFile.write("PBBSCENE", 8);
	outFile.write("0000", 4); // Bytes 8-11

	uint32_t numGameObjects = GetNumGameObjects(buffer);
	uint32_t sizeOfGameObjects = numGameObjects * sizeOfGameObject;
	uint32_t numComponents = GetNumComponents(buffer);
	uint32_t gameObjectOffset = PB_HEADER_LENGTH;
	uint32_t componentsOffset = PB_HEADER_LENGTH + sizeOfGameObjects;
	uint32_t sceneDataAssetID = AssetMapSaver::NextAssetMapIndex();

	outFile.write((char*)&gameObjectOffset, 4);
	outFile.write((char*)&componentsOffset, 4);
	outFile.write((char*)&sceneDataAssetID, 4);
	outFile.write("0000", 4);
	outFile.write((char*)&numComponents, 4);
	outFile.write((char*)&numGameObjects, 4);

	std::string name = GetName(buffer);
	outFile.write(name.c_str(), 32);
}

uint32_t SceneConverter::GetNumGameObjects(const FileBuffer & buffer)
{
	uint32_t numGameObjects = 0;
	for (size_t i = 0; i < buffer.Size(); i++)
	{
		if (buffer.CompareSubstr("Transform: ", i))
		{
			numGameObjects++;
			i += 20; // Figure out good number later
		}
	}
	return numGameObjects;
}

uint32_t SceneConverter::GetNumComponents(const FileBuffer & buffer)
{
	uint32_t numComponents = 0;
	for (size_t i = 0; i < buffer.Size(); i++)
	{
		if (buffer.CompareSubstr("ClassID:", i))
		{
			numComponents++;
			i += 10; // Figure out good number later
		}
	}
	return numComponents;
}

std::string SceneConverter::GetName(const FileBuffer & buffer)
{
	size_t indexOfName = buffer.Find("Name: ");
	size_t indexOfNewLine = buffer.Find('\n', indexOfName);
	return buffer.Substr(indexOfName, indexOfNewLine);
}

void SceneConverter::GenerateGameObject(const FileBuffer & buffer, std::ofstream & outFile)
{
	std::vector<GameObjectInfo> gameObjectInfos = GenerateGameObjectInfos(buffer);

	for (size_t i = 0; i < gameObjectInfos.size(); i++)
	{
		SaveGameObject(gameObjectInfos[i], outFile);
	}
}

std::vector<SceneConverter::GameObjectInfo> SceneConverter::GenerateGameObjectInfos(const FileBuffer & buffer)
{
	std::vector<GameObjectInfo> gameObjects;

	// Generate Game Objects
	size_t firstBrace = buffer.Find('{');
	size_t lastBrace = buffer.ReverseFind('}');
	ParseGameObject(buffer, gameObjects, 0, firstBrace, lastBrace);

	return gameObjects;
}

void SceneConverter::ParseGameObject(const FileBuffer & buffer, std::vector<GameObjectInfo>& gameObjects, size_t parentIndex, size_t start, size_t end)
{
	GameObjectInfo info;
	info.parentIndex = parentIndex;
	info.tempID = gameObjects.size();
	std::string str = "Name: ";

	size_t currentPosition = buffer.Find("Name: ", start);
	info.name = buffer.Substr(currentPosition + 6, buffer.Find('\n', currentPosition));

	currentPosition = buffer.Find("Transform: ", currentPosition);
	std::vector<float> transform = LString::StringToFloatVector(buffer.Substr(currentPosition + 11, buffer.Find('\n', currentPosition)));
	info.position = FVector3(transform[0], transform[1], transform[2]);
	info.rotation = FQuaternion(transform[3], transform[4], transform[5], transform[6]);
	info.scale = FVector3(transform[7], transform[8], transform[9]);

	currentPosition = buffer.Find("Tag: ", currentPosition);
	info.tag = (uint16_t)LString::StringToUInt(buffer.Substr(currentPosition + 5, buffer.Find('\n', currentPosition)));

	currentPosition = buffer.Find("Layer: ", currentPosition);
	info.layer = (uint16_t)LString::StringToUInt(buffer.Substr(currentPosition + 7, buffer.Find('\n', currentPosition)));

	currentPosition = buffer.Find("Children: ", currentPosition);

	size_t namePosition = buffer.Find("Name: ", currentPosition);
	size_t bracketPosition = buffer.Find("[]", currentPosition);
	bool hasChildren = bracketPosition > namePosition;

	if (hasChildren)
	{
		currentPosition += 10;
		gameObjects.push_back(info);
		size_t endPosition = 0;
		size_t childrenEndPosition = FindEndBrace(buffer, currentPosition);
		while (endPosition + 12 < childrenEndPosition)
		{
			endPosition = (size_t)LMath::Min((int)buffer.Find("},{", currentPosition), (int)buffer.Find("}\n", currentPosition));
			if (endPosition > buffer.Size()) 
				return;
			ParseGameObject(buffer, gameObjects, info.tempID, currentPosition + 4, endPosition);
			currentPosition = endPosition + 4;
		}
	}
	else
	{
		info.numChildren = 0;
		gameObjects.push_back(info);
	}
}

void SceneConverter::SaveGameObject(const GameObjectInfo & info, std::ofstream & outFile)
{
	char trueChar = 1;
	outFile.write("A", 1);
	outFile.write((char*)&info.layer, 1);
	outFile.write((char*)&info.tag, 2);
	outFile.write((char*)&info.parentIndex, 4);
	outFile.write((char*)&info.numChildren, 1);
	outFile.write(&trueChar, 1);
	outFile.write("AA", 2);
	outFile.write((char*)&info.position, 12);
	outFile.write((char*)&info.rotation, 16);
	outFile.write((char*)&info.scale, 12);
	outFile.write((char*)&info.tempID, 4);
	outFile.write(info.name.c_str(), 32);
}

size_t SceneConverter::FindEndBrace(const FileBuffer & buffer, size_t start)
{
	uint8_t levelsDeep = 0;
	for (size_t i = start; i < buffer.Size(); i++)
	{
		if (buffer[i] == '[')
		{
			levelsDeep++;
		}
		else if (buffer[i] == ']')
		{
			levelsDeep--;
			if (levelsDeep == 0) return i;
		}
	}

	return std::string::npos;
}

void SceneConverter::GenerateComponent(const FileBuffer & buffer, std::ofstream & outFile)
{
	size_t currentPosition = 0;
	size_t currentGameObject = 0;

	while (currentPosition < buffer.Size())
	{
		currentPosition = buffer.Find("Components: ", currentPosition);
		if (currentPosition == std::string::npos) break;

		if (buffer.CompareSubstr("[]", currentPosition + 12))
		{
			currentGameObject++;
			currentPosition += 20;
			continue;
		}

		size_t startPosition = currentPosition + 11;
		size_t endPosition = FindEndBrace(buffer, currentPosition);
		ParseComponents(buffer, outFile, currentGameObject, startPosition, endPosition);

		currentPosition += 20;
		currentGameObject++;
	}
}

void SceneConverter::ParseComponents(const FileBuffer & buffer, std::ofstream & outFile, uint32_t gameObject, size_t start, size_t end)
{
	size_t currentPosition = start;

	while (currentPosition < end)
	{
		size_t bracePosition = FindEndCurlyBrace(buffer, currentPosition);
		currentPosition = buffer.Find("ClassID: ", currentPosition);
		if (currentPosition >= end) break;

		size_t newLinePosition = buffer.Find('\n', currentPosition);
		unsigned int classID = LString::StringToUInt(buffer.Substr(currentPosition + 8, newLinePosition));
		CodeClass& componentClass = EditorProject::GetClassOfId(classID);
		currentPosition = buffer.Find("Params:", currentPosition);

		std::string paramString = buffer.Substr(currentPosition + 8, bracePosition);
		std::vector<std::string> params = LString::SeperateStringByChar(paramString, '\n', true);
		uint16_t numParams = params.size();
		uint16_t paramSize = LSerializationOperations::SerializedSizeOf(componentClass, EditorProject::gameProject, ECodingLanguage::CPlusPlus);
		
		outFile.write((char*)&classID, 4);
		outFile.write((char*)&gameObject, 4);
		outFile.write((char*)&numParams, 2);
		outFile.write((char*)&paramSize, 2);

		if (LString::IsOnlyWhitespace(params[params.size() - 1])) 
			params.pop_back();

		LSerializationOperations::ConvertToBinary(params, componentClass, EditorProject::gameProject, outFile);

		currentPosition = buffer.Find('}', currentPosition) + 1;
	}
}

size_t SceneConverter::FindEndCurlyBrace(const FileBuffer & buffer, size_t start)
{
	uint8_t levelsDeep = 0;
	for (size_t i = start; i < buffer.Size(); i++)
	{
		if (buffer[i] == '{')
		{
			levelsDeep++;
		}
		else if (buffer[i] == '}')
		{
			levelsDeep--;
			if (levelsDeep == 0) return i;
		}
	}

	return std::string::npos;
}
