#include "GeneratedEditor.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "../BuildSystem/LSerializationOperations.h"
#include "../CodeParser/Cpp/LCpp.h"
#include "../CodeParser/CodeClass.h"
#include "../CodeParser/CodeProject.h"
#include "../Framework/EditorProject.h"

GeneratedEditor::GeneratedEditor()
{
	this->classId = 0;
}

GeneratedEditor::GeneratedEditor(unsigned int classId)
{
	this->classId = classId;
	this->component = nullptr;

	GenerateSerializedFields();
}

GeneratedEditor::GeneratedEditor(unsigned int classId, Component * component)
{
	this->classId = classId;
	this->component = component;

	GenerateSerializedFields();
}

void GeneratedEditor::Display(Component * component)
{
	if (this->component == nullptr) return;

	for (size_t i = 0; i < this->serializedFields.size(); i++)
	{
		DisplayParamType(serializedFields[i], component);
	}
}

void GeneratedEditor::GenerateSerializedFields()
{
	CodeProject& project = EditorProject::gameProject;

	FComponentInfo componentInfo = EditorProject::componentClasses.Get(this->classId);
	CodeClass& codeClass = project.classes[project.FindIndexOfClass(componentInfo.name)];

	// Move this later
	this->serializedFields.clear();
	size_t currentOffset = sizeof(Component);
	for (size_t i = 0; i < codeClass.params.size(); i++)
	{
		auto optionalParamType = LSerializationOperations::TypenameToParamType(codeClass.params[i].type, project);
		
		// If can't figure out type, ignore it
		if (!optionalParamType)
		{
			continue;
		}

		size_t paramSize = LSerializationOperations::SizeOfParam(codeClass.params[i], project, ECodingLanguage::CPlusPlus);
		currentOffset = LCpp::AlignForward(currentOffset, paramSize);
		currentOffset += paramSize;

		if (codeClass.params[i].accessType != ECodeAccessType::Public) continue;

		FSerializationInfo& info = serializedFields.emplace_back();
		info.type = optionalParamType.value();
		info.typeName = codeClass.params[i].type;
		info.offset = currentOffset - paramSize;
		info.name = codeClass.params[i].name;
	}
}

void GeneratedEditor::DisplayParamType(FSerializationInfo & serializedField, Component* component)
{
	const char* name = serializedField.name.c_str();
	switch (serializedField.type)
	{
	case EParamType::AUDIO:
		Debug::LogError("Audio Display is not complete"); break;
	case EParamType::BOOL:
		ImGui::Checkbox(name, (bool*)((char*)component + serializedField.offset)); break;
	case EParamType::BOX:
		LImGui::DisplayBox(*(FBox*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::BYTE:
		ImGui::DragInt(name, (int*)((char*)component + serializedField.offset), 1, -128, 128); break;
	case EParamType::COLOR:
		ImGui::ColorEdit4(name, (float*)((char*)component + serializedField.offset, ImGuiColorEditFlags_Float));
		break;
	case EParamType::CURVE:
		Debug::LogError("Curve Display is not complete"); break;
	case EParamType::DATA:
		Debug::LogError("Data Display is not complete"); break;
	case EParamType::DOUBLE:
		// This will not work
		ImGui::DragFloat(name, (float*)(double*)((char*)component + serializedField.offset)); break;
	case EParamType::FILE:
		LImGui::DisplayFileAsset(*(FileRef*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::FLOAT:
		ImGui::DragFloat(name, (float*)((char*)component + serializedField.offset), 10, -10000000, 10000000); break;
	case EParamType::FONT:
		LImGui::DisplayFontAsset(*(FontRef*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::INT:
		ImGui::DragInt(name, (int*)((char*)component + serializedField.offset)); break;
	case EParamType::LONG:
		ImGui::DragInt(name, (int*)(long long*)((char*)component + serializedField.offset)); break;
	case EParamType::MATERIAL:
		Debug::LogError("Material Display is not complete"); break;
	case EParamType::MESH:
		LImGui::DisplayMeshAsset(*(MeshRef*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::QUATERNION:
		LImGui::DisplayQuaternion(*(FQuaternion*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::RECT:
		LImGui::DisplayRect(*(FRect*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::SHADER:
		Debug::LogError("Shader Display is not complete"); break;
	case EParamType::SHORT:
		ImGui::DragInt(name, (int*)(short*)((char*)component + serializedField.offset), 1, -32767, 32767); break;
	case EParamType::SPHERICALPOINT:
		Debug::LogError("Spherical Point Display is not complete"); break;
	case EParamType::STRING:
		LImGui::DisplayString(name, (std::string*)((char*)component + serializedField.offset)); break;
	case EParamType::TEXT:
		LImGui::DisplayTextAsset(*(TextRef*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::TEXTURE:
		LImGui::DisplayTextureAsset(*(TextureRef*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::VECTOR2:
		LImGui::DisplayVector2(*(FVector2*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::VECTOR3:
		LImGui::DisplayVector3(*(FVector3*)((char*)component + serializedField.offset), serializedField.name); break;
	case EParamType::VECTOR4:
		LImGui::DisplayVector4(*(FVector4*)((char*)component + serializedField.offset), serializedField.name); break;
	}
}
