#include "SceneSaver.h"
#include "EditorProject.h"
#include "SaveParams.h"
#include "../BuildSystem/LSerializationOperations.h"
#include "Runtime/Framework/Framework.h"
#include "Runtime/Framework/Project.h"

void SceneSaver::SaveGameObject(GameObject * gameObject, std::ofstream& stream)
{
	stream << "\tName: " << gameObject->name << std::endl;
	
	if (gameObject->isUI)
	{
		stream << "\tRectTransform: ";
		stream << ConstraintTextFromType(gameObject->rectTransform.xConstraint.type) << " " << gameObject->rectTransform.xConstraint.value << " ";
		stream << ConstraintTextFromType(gameObject->rectTransform.yConstraint.type) << " " << gameObject->rectTransform.yConstraint.value << " ";
		stream << ConstraintTextFromType(gameObject->rectTransform.widthConstraint.type) << " " << gameObject->rectTransform.widthConstraint.value << " ";
		stream << ConstraintTextFromType(gameObject->rectTransform.heightConstraint.type) << " " << gameObject->rectTransform.heightConstraint.value;
		stream << std::endl;
	}
	else
	{
		stream << "\tTransform: ";
		stream << gameObject->localPosition.x << " " << gameObject->localPosition.y << " " << gameObject->localPosition.z << " ";
		stream << gameObject->localRotation.x << " " << gameObject->localRotation.y << " " << gameObject->localRotation.z << " " << gameObject->localRotation.w << " ";
		stream << gameObject->localScale.x << " " << gameObject->localScale.y << " " << gameObject->localScale.z << std::endl;
	}

	stream << "\tTag: " << gameObject->tag << std::endl;
	stream << "\tLayer: " << (unsigned short)gameObject->layer << std::endl;

	std::vector<unsigned int> componentIDs = Project::componentManager->GetComponentsIDsInGameObject(gameObject);
	std::vector<Component*> components = Project::componentManager->GetComponentsInGameObject(gameObject);

	if (componentIDs.size() == 0)
	{
		stream << "\tComponents: []" << std::endl;
	}
	else
	{
		stream << "\tComponents: [";
		for (int i = 0; i < components.size() - 1; i++)
		{
			stream << "{" << std::endl << "\t\tClassID: " << componentIDs[i] << std::endl << "\t\tParams: " << std::endl;
			LSerializationOperations::SaveToText(components[i], componentIDs[i], EditorProject::gameProject, stream);
			stream << "},";
		}

		size_t lastIndex = components.size() - 1;
		stream << "{" << std::endl << "\t\tClassID: " << componentIDs[lastIndex] << std::endl << "\t\tParams: " << std::endl;
		LSerializationOperations::SaveToText(components[lastIndex], componentIDs[lastIndex], EditorProject::gameProject, stream);
		stream << "\t}]" << std::endl;
	}

	if (gameObject->children.size() == 0)
	{
		stream << "\tChildren: []" << std::endl;
	}
	else
	{
		stream << "\tChildren: [";
		for (int i = 0; i < gameObject->children.size() - 1; i++)
		{
			stream << "{" << std::endl;
			SaveGameObject(gameObject->children[i], stream);
			stream << "},";
		}
		stream << "{" << std::endl;
		SaveGameObject(gameObject->children[gameObject->children.size() - 1], stream);
		stream << "}]" << std::endl;
	}
}

void SceneSaver::SaveSceneSettings(SceneSettings& settings, std::ofstream& stream)
{
	stream << "Settings: [" << std::endl;
	stream << "\tClearColor: "; SaveColor(settings.clearColor, stream); stream << std::endl;
	stream << "\tUISortMode: "; SaveUByte((uint8_t)settings.uiSortMode, stream); stream << std::endl;
	stream << "\tAudioPlayback: "; SaveBool(settings.audioPlayback, stream); stream << std::endl;
	stream << "\tInputMask: "; SaveUShort(settings.inputMask, stream); stream << std::endl;
	stream << "]" << std::endl;
}

bool SceneSaver::SaveScene(uint8_t sceneIndex, const std::string& filename)
{
	if (sceneIndex >= MAX_SCENES)
	{
		Debug::LogError("Invalid Scene");
		return false;
	}
	if (!Scene::IsLoaded(sceneIndex))
	{
		Debug::errorLog << "Scene at index " << sceneIndex << " is not loaded" << Debug::endl;
		return false;
	}
	if (!LFileOperations::DoesFileHaveExtension(filename, "pbscene"))
	{
		Debug::LogError("Loaded Scene is not a .pbscene file");
		return false;
	}

	std::ofstream sceneFile(filename);
	if (sceneFile.fail())
	{
		Debug::LogError("File " + filename + " could not be opened");
		return false;
	}

	// PROFILE_SCOPE("Save Scene");

	sceneFile << "PROJECT BLOO SCENE" << std::endl;
	sceneFile << "Name: " << LFileOperations::StripFilenameAndExt(filename) << std::endl;
	sceneFile << "Project: " << Project::projectName << std::endl;

	SaveSceneSettings(Scene::scenes[sceneIndex].sceneSettings, sceneFile);

	sceneFile << "{" << std::endl;
	SaveGameObject(&Scene::scenes[sceneIndex].sceneRoot, sceneFile);
	sceneFile << "}" << std::endl;

	return true;
}
