#include "FileView.h"
#include <filesystem>
#include "Runtime/Debug/Debug.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Input/Input.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "Runtime/Rendering/Managers/MeshManager.h"
#include "Runtime/Rendering/Managers/TextureManager.h"
#include "../AssetViewers/MeshViewer.h"
#include "../AssetViewers/ImageViewer.h"
#include "../Core/EditorApplication.h"
#include "../Core/FileDialog.h"
#include "../Framework/CreateMenu.h"
#include "../Framework/CreateSystem.h"
#include "../Framework/ImportSystem.h"
namespace fs = std::filesystem;

FileView* FileView::fileView = nullptr;

bool openCppMenu = false;
bool openMaterialMenu = false;

FileView::FileView()
{
	this->name = "Files";
	this->category = EEditorModuleCategory::Core;

	this->assetFilePath = EditorApplication::assetsFilePath;

	this->directories = LFileOperations::CreateFileNamesTree(this->assetFilePath, EFileTreeOptions::DisplayDirectories);

	for (int i = 0; i < 18; i++)
	{
		this->filesSelected[i] = true;
	}

	fileView = this;
}

FileView::~FileView()
{
	delete directories;

	fileView = nullptr;
}

void FileView::DisplayCreateMenu()
{
	if (ImGui::MenuItem("C++ Class"))
	{
		openCppMenu = true;
	}
	ImGui::Separator();
	if (ImGui::MenuItem("Material"))
	{
		openMaterialMenu = true;
	}
	if (ImGui::MenuItem("Shader"))
	{

	}
	ImGui::Separator();
	if (ImGui::MenuItem("Datatable"))
	{
		CreateSystem::CreateDatatable(this->selectedFilepath);
	}
	ImGui::Separator();
	if (ImGui::MenuItem("Scene"))
	{
		CreateSystem::CreateScene(this->selectedFilepath);
	}
}

void FileView::DisplayImportMenu()
{
	FFileDialogInfo dialog = FileDialog::OpenFile(nullptr);
	if (!dialog.IsValid())
	{
		return;
	}

	ImportSystem::Import(dialog.filename, this->selectedFilepath);
}

void FileView::DisplayContextMenu()
{
	if (ImGui::BeginPopup("##Menu"))
	{
		if (ImGui::BeginMenu("Create ..."))
		{
			DisplayCreateMenu();
			ImGui::EndMenu();
		}
		if (ImGui::Selectable("Import"))
		{
			DisplayImportMenu();
		}
		ImGui::EndPopup();
	}

	OpenCreateMenus();
}

void FileView::DisplayTree()
{
	ImGui::BeginChild("Directories", ImVec2(200, 0), true);

	LImGui::DisplayTree(directories, "Assets", this->selectedItem);

	std::string tempSelectedItem = selectedItem;
	TTypedTreeNode<std::string>* selectedNode = SearchTree<std::string>(directories, [&tempSelectedItem](std::string str) { return str == tempSelectedItem; });

	if (selectedItem == "Assets")
	{
		this->selectedFilepath = this->assetFilePath;
	}
	else
	{
		this->selectedFilepath = this->assetFilePath + "/" + GetSelectedFilepath(selectedNode);
	}

	ImGui::EndChild();
}

void FileView::DisplayContents()
{
	FRect rect = GetWindowRect();
	ImGui::SameLine();
	ImGui::BeginChild("Contents", ImVec2(rect.GetWidth() - 300, 0), true);

	static std::vector<std::string> fileTypes = { "Audio", "Animation", "Code",
		"Data", "Font", "Image", "H", "Markup", "Material", "Mesh", "Meta", 
		"NonEngineCode", "Particle", "Prefab", "Shader", "Scene", "Text","Video" 
	};
	Filemask fileMask = LImGui::DisplayBitmask("Filters", fileTypes, filesSelected);
	fileMask.SetBitTrue((uint8_t)EAssetType::Directory);

	if (this->selectedFilepath.empty())
	{
		ImGui::EndChild();
		return;
	}

	ImGui::Text("Contents");

	for (auto& p : fs::directory_iterator(this->selectedFilepath))
	{
		std::string pathString = p.path().filename().string();
		EAssetType type = LFileOperations::GetFileType(pathString);

		if (!fileMask.CompareFile(FFileCategory(type, false)))
		{
			continue;
		}

		if (ImGui::Button(pathString.c_str()))
		{
			if (p.is_directory())
			{
				this->selectedItem = pathString;
			}
			else
			{
				switch (type)
				{
				case EAssetType::Mesh:
				{
					MeshViewer* meshViewer = (MeshViewer*)EditorApplication::AddModule(new MeshViewer());
					meshViewer->loadedRef = MeshManager::LoadMesh(p.path().string());
				}
					break;
				case EAssetType::Image:
				{
					ImageViewer* imageViewer = (ImageViewer*)EditorApplication::AddModule(new ImageViewer());
					imageViewer->loadedRef = TextureManager::LoadTexture(p.path().string());
				}
					break;
				}
			}
		}
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			std::string dragDropType = GetDragDropTypeFromAssetType(type);
			std::string fullPathString = p.path().string();
			ImGui::SetDragDropPayload(dragDropType.c_str(), fullPathString.c_str(), fullPathString.size() + 1);
			ImGui::EndDragDropSource();
		}
	}

	ImGui::EndChild();
}

void FileView::OpenCreateMenus()
{
	if (openCppMenu)
	{
		ImGui::OpenPopup("Create C++ Class");
		openCppMenu = false;
	}
	if (openMaterialMenu)
	{
		ImGui::OpenPopup("Create Material");
		openMaterialMenu = false;
	}

	CreateMenu::DisplayCreateMenu();
}

std::string FileView::GetSelectedFilepath(TTypedTreeNode<std::string>* selectedNode)
{
	if (selectedNode == nullptr)
	{
		return "";
	}

	std::string filePath = selectedNode->object;
	TTypedTreeNode<std::string>* current = selectedNode;

	while (true)
	{
		if (current->parentNode == nullptr || current->parentNode->parentNode == nullptr)
		{
			return filePath;
		}
		current = current->parentNode;
		filePath = current->object + "/" + filePath;
	}

	return filePath;
}

void FileView::Display()
{
	DisplayContextMenu();
	DisplayTree();
	DisplayContents();
}

void FileView::HandleInput()
{
	if (Input::GetMouseButtonUp(EMouseButton::Right))
	{
		ImGui::OpenPopup("##Menu");
	}
}

void FileView::Reload()
{
	delete directories;

	this->directories = LFileOperations::CreateFileNamesTree(this->assetFilePath, EFileTreeOptions::DisplayDirectories);
}

std::string FileView::GetDragDropTypeFromAssetType(EAssetType type)
{
	switch (type)
	{
	case EAssetType::Mesh: return "EXPERIO_MESH";
	case EAssetType::Image: return "EXPERIO_IMAGE";
	}
	return "";
}

bool FileView::IsAssetLoaded(const std::string& filepath, EAssetType type)
{
	switch (type)
	{
	case EAssetType::Mesh:
		return MeshManager::IsMeshLoaded(filepath);
	case EAssetType::Image:
		return TextureManager::IsTextureLoaded(filepath);
	}
	return false;
}
