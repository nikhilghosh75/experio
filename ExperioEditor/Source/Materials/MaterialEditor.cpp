#include "MaterialEditor.h"
#include "../Framework/EditorProject.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

MaterialEditor::MaterialEditor()
{
	this->name = "Material Editor";
	this->category = EEditorModuleCategory::Viewer;
}

void MaterialEditor::Display()
{
	ImGui::Text(materialName.c_str());
	for (size_t i = 0; i < shaderInfo.uniforms.size(); i++)
	{
		DisplayUniform(shaderInfo.uniforms[i]);
	}
}

void MaterialEditor::SetMaterial(const std::string & str)
{
	this->material = Project::materialManager->LoadMaterialFromFile(str);
	this->materialType = Project::materialManager->GetLastMaterialType();
	this->shaderInfo = EditorProject::shaders[this->materialType - 1];
	this->materialName = LFileOperations::StripFilename(str);
}

void MaterialEditor::SetMaterial(Material * material, uint32_t materialType)
{
	this->material = material;
	this->materialType = materialType;
	this->shaderInfo = EditorProject::shaders[this->materialType - 1];;
	this->materialName = "Name Unknown";
}

void MaterialEditor::DisplayUniform(ShaderParamInfo paramInfo)
{
	switch (paramInfo.type)
	{
	case EShaderParamType::BOOL:
		ImGui::Checkbox(paramInfo.name.c_str(), (bool*)((char*)material + paramInfo.offset)); break;
	case EShaderParamType::TEXTURE:
		TextureRef& ref = *(TextureRef*)((char*)material + paramInfo.offset);
		LImGui::DisplayTextureAsset(*(TextureRef*)((char*)material + paramInfo.offset), paramInfo.name); 
		ImGui::Image((void*)ref->GetRendererID(), ImVec2(100, 100));
		break;
	}
}
