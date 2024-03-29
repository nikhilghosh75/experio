#include "MaterialEditor.h"
#include "../Framework/EditorProject.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "MaterialSaver.h"

MaterialEditor* MaterialEditor::materialEditor;

MaterialEditor::MaterialEditor()
{
	this->name = "Material Editor";
	this->category = EEditorModuleCategory::Viewer;

	this->locked = false;

	materialEditor = this;
}

void MaterialEditor::Display()
{
	if (locked)
	{
		ImGui::Text("Material Editing is Locked");
		return;
	}

	ImGui::Text(materialName.c_str());
	for (size_t i = 0; i < shaderInfo.uniforms.size(); i++)
	{
		DisplayUniform(shaderInfo.uniforms[i]);
	}

	if (filepath.size() > 4)
	{
		if (ImGui::Button("Save Material"))
		{
			SaveMaterial();
		}
	}
}

void MaterialEditor::SaveMaterial()
{
	MaterialSaver::SaveMaterial(material, materialType, filepath);
}

void MaterialEditor::SetMaterial(const std::string & str)
{
	this->material = Project::materialManager->LoadMaterialFromFile(str);
	this->materialType = Project::materialManager->GetLastMaterialType();
	this->shaderInfo = EditorProject::shaders[this->materialType - 1];
	this->materialName = LFileOperations::StripFilename(str);
	this->filepath = str;
}

void MaterialEditor::SetMaterial(Material * material, uint32_t materialType)
{
	this->material = material;
	this->materialType = materialType;
	this->shaderInfo = EditorProject::shaders[this->materialType - 1];
	this->materialName = "Name Unknown";
	this->filepath = " ";
}

void MaterialEditor::Lock()
{
	locked = true;
}

void MaterialEditor::Unlock()
{
	locked = false;
}

void MaterialEditor::DisplayUniform(ShaderParamInfo paramInfo)
{
	switch (paramInfo.type)
	{
	case EShaderParamType::BOOL:
		ImGui::Checkbox(paramInfo.name.c_str(), (bool*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::FLOAT:
		ImGui::DragFloat(paramInfo.name.c_str(), (float*)((char*)material + paramInfo.offset), 10, -10000000, 10000000); break;
	case EShaderParamType::FLOAT2:
		ImGui::DragFloat2(paramInfo.name.c_str(), (float*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::FLOAT3:
		ImGui::DragFloat3(paramInfo.name.c_str(), (float*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::FLOAT4:
		ImGui::DragFloat4(paramInfo.name.c_str(), (float*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::INT:
		ImGui::DragInt(paramInfo.name.c_str(), (int*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::INT2:
		ImGui::DragInt2(paramInfo.name.c_str(), (int*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::INT3:
		ImGui::DragInt3(paramInfo.name.c_str(), (int*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::INT4:
		ImGui::DragInt4(paramInfo.name.c_str(), (int*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::TEXTURE:
		TextureRef& ref = *(TextureRef*)((char*)material + paramInfo.offset);
		LImGui::DisplayTextureAsset(*(TextureRef*)((char*)material + paramInfo.offset), paramInfo.name); 
		ImGui::Image((void*)ref->GetRendererID(), ImVec2(100, 100));
		break;
	}
}
