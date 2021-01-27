#include "MemoryProfiler.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Data/DataManager.h"
#include "Runtime/Framework/Scene.h"
#include "Runtime/Rendering/Managers/FontManager.h"
#include "Runtime/Rendering/Managers/MeshManager.h"
#include "Runtime/Rendering/Managers/TextureManager.h"
#include "Runtime/Rendering/Shaders/Shader.h"

void MemoryProfiler::Calculate()
{
	this->datatableSize = DataManager::SizeOfLoadedTables();
	this->fontSize = FontManager::SizeOfLoadedFonts();
	this->gameObjectSize = Scene::SizeOfLoadedScenes();
	this->meshSize = MeshManager::SizeOfLoadedMeshes();
	this->shaderSize = Shader::SizeOfLoadedShaders();
	this->textureSize = TextureManager::SizeOfLoadedTextures();
}

size_t MemoryProfiler::GetTotalSize() const
{
	return datatableSize + fontSize + gameObjectSize + meshSize
		+ shaderSize + textureSize;
}

MemoryProfiler::MemoryProfiler()
{
	this->category = EEditorModuleCategory::Profiling;
	this->name = "Memory Profiler";

	this->datatableSize = 0;
	this->fontSize = 0;
	this->gameObjectSize = 0;
	this->meshSize = 0;
	this->shaderSize = 0;
	this->textureSize = 0;
}

void MemoryProfiler::Display()
{
	if (shouldCalculate)
		Calculate();

	ImGui::Checkbox("Calculating", &shouldCalculate);

	ImGui::Text("Current Memory Usage (in bytes)");
	ImGui::Separator();

	ImGui::Text("Datatables: "); ImGui::SameLine(); ImGui::Text(LString::NumberWithCommas(datatableSize).c_str());
	ImGui::Text("Fonts: "); ImGui::SameLine(); ImGui::Text(LString::NumberWithCommas(fontSize).c_str());
	ImGui::Text("Game Objects: "); ImGui::SameLine(); ImGui::Text(LString::NumberWithCommas(gameObjectSize).c_str());
	ImGui::Text("Meshes: "); ImGui::SameLine(); ImGui::Text(LString::NumberWithCommas(meshSize).c_str());
	ImGui::Text("Shaders: "); ImGui::SameLine(); ImGui::Text(LString::NumberWithCommas(shaderSize).c_str());
	ImGui::Text("Textures: "); ImGui::SameLine(); ImGui::Text(LString::NumberWithCommas(textureSize).c_str());
	
	ImGui::Separator();

	ImGui::Text("Total: "); ImGui::SameLine(); ImGui::Text(LString::NumberWithCommas(GetTotalSize()).c_str());
}
