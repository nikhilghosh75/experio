#include "FileView.h"
#include <filesystem>
#include "Runtime/Data/DataManager.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Debug/Profiler.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Input/Input.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "Runtime/Rendering/Managers/FontManager.h"
#include "Runtime/Rendering/Managers/MeshManager.h"
#include "Runtime/Rendering/Managers/TextureManager.h"
#include "../AssetViewers/FontViewer.h"
#include "../AssetViewers/ImageViewer.h"
#include "../AssetViewers/InputMapViewer.h"
#include "../AssetViewers/MeshViewer.h"
#include "../Core/EditorApplication.h"
#include "../Core/FileDialog.h"
#include "../Framework/CreateMenu.h"
#include "../Framework/CreateSystem.h"
#include "../Framework/ImportSystem.h"
#include "../Materials/MaterialEditor.h"
namespace fs = std::filesystem;

FileView* FileView::fileView = nullptr;

bool openCppMenu = false;
bool openMaterialMenu = false;
bool openFolderMenu = false;

FileView::FileView()
{
	this->name = "Files";
	this->category = EEditorModuleCategory::Core;

	this->flags = ImGuiWindowFlags_MenuBar;

	this->assetFilePath = EditorApplication::assetsFilePath;
	this->selectedItem = "Assets";

	this->directories = LFileOperations::CreateFileNamesTree(this->assetFilePath, EFileTreeOptions::DisplayDirectories);

	this->fileMask.SetBitsTrue();
	for (int i = 0; i < 21; i++)
	{
		this->filesSelected[i] = true;
	}

	memset(searchBuffer, 0, 64);

	this->viewMode = EFileViewMode::Button;

	fileView = this;
}

FileView::~FileView()
{
	delete directories;

	fileView = nullptr;
}

void FileView::DisplayCreateMenu()
{
	if (ImGui::MenuItem("Folder"))
	{
		openFolderMenu = true;
	}
	ImGui::Separator();
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
	ImGui::Separator();
	if (ImGui::MenuItem("Text"))
	{
		CreateSystem::CreateText(this->selectedFilepath);
	}
}

void FileView::DisplayImportMenu()
{
	std::vector<FFileDialogInfo> dialogs = FileDialog::OpenMultipleFiles(nullptr);

	for (size_t i = 0; i < dialogs.size(); i++)
	{
		ImportSystem::Import(dialogs[i].filename, this->selectedFilepath);
	}
}

void FileView::DisplayMenuBar()
{
	static const std::vector<std::string> fileTypes = { "Audio", "Animation", "Code",
		"Data", "Flowchart", "Font", "H", "Image", "Input Map", "Markup", "Material", "Mesh", 
		"Meta", "NonEngineCode", "Particle", "Prefab", "Shader", "Scene", "Soundbank", 
		"Style", "Text","Video"
	};
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::Selectable("Button View", viewMode == EFileViewMode::Button))
				viewMode = EFileViewMode::Button;
			if (ImGui::Selectable("Table View", viewMode == EFileViewMode::Table))
				viewMode = EFileViewMode::Table;

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Filters"))
		{
			fileMask = LImGui::DisplayBitmask("Filters", fileTypes, filesSelected);
			fileMask.SetBitTrue((uint8_t)EAssetType::Directory);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
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

	std::string tempSelectedItem = this->selectedItem;
	LImGui::DisplayTree(directories, "Assets", tempSelectedItem);

	if (tempSelectedItem != this->selectedItem)
	{
		TTypedTreeNode<std::string>* selectedNode = SearchTree<std::string>(directories, [&tempSelectedItem](std::string str) { return str == tempSelectedItem; });
		this->selectedItem = tempSelectedItem;

		if (selectedItem == "Assets")
		{
			this->selectedFilepath = this->assetFilePath;
		}
		else
		{
			this->selectedFilepath = this->assetFilePath + "/" + GetSelectedFilepath(selectedNode);
		}
	}

	ImGui::EndChild();
}

void FileView::DisplayContents()
{
	FRect rect = GetWindowRect();
	ImGui::SameLine();
	ImGui::BeginChild("Contents", ImVec2(rect.GetWidth() - 300, 0), true);

	if (this->selectedFilepath.empty())
	{
		this->selectedFilepath = this->assetFilePath;
		ImGui::EndChild();
		return;
	}

	ImGui::Text("Contents");

	ImGui::Text(selectedFilepath.c_str());
	ImGui::SameLine();
	bool searchChanged = ImGui::InputText("##Search", searchBuffer, 64);

	if (searchChanged || strlen(searchBuffer) > 0)
	{
		DisplaySearch();
	}
	else if (viewMode == EFileViewMode::Button)
	{
		DisplayContentsButtonView();
	}
	else
	{
		DisplayContentsTableView();
	}

	ImGui::EndChild();
}

void FileView::DisplayContentsButtonView()
{
	for (auto& p : fs::directory_iterator(this->selectedFilepath))
	{
		std::string pathString = p.path().filename().string();
		EAssetType type = LFileOperations::GetFileType(pathString);

		if (type == EAssetType::Meta)
		{
			continue;
		}

		if (!fileMask.CompareFile(FFileCategory(type, false)))
		{
			continue;
		}

		if (ImGui::Button(pathString.c_str()))
		{
			if (p.is_directory())
			{
				this->selectedItem = pathString;
				this->selectedFilepath = p.path().string();
				break;
			}
			else
			{
				this->OpenFile(p.path().string(), type);
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
}

void FileView::DisplayContentsTableView()
{
	if (ImGui::BeginTable("##Contents", 3))
	{
		ImGui::TableSetupColumn("Filename");
		ImGui::TableSetupColumn("Type");
		ImGui::TableSetupColumn("Size");
		ImGui::TableHeadersRow();

		for (auto& p : fs::directory_iterator(this->selectedFilepath))
		{
			std::string pathString = p.path().filename().string();
			EAssetType type = LFileOperations::GetFileType(pathString);
			size_t size = fs::file_size(p);

			if (type == EAssetType::Meta)
			{
				continue;
			}

			if (!fileMask.CompareFile(FFileCategory(type, false)))
			{
				continue;
			}

			ImGui::TableNextColumn();
			ImGui::Text(pathString.c_str());

			ImGui::TableNextColumn();
			ImGui::Text(LFileOperations::AssetTypeToString(type).c_str());

			ImGui::TableNextColumn();
			ImGui::Text(LFileOperations::BytesToString(size, 2).c_str());
		}

		ImGui::EndTable();
	}
}

void FileView::DisplaySearch()
{
	if (ImGui::BeginTable("##Contents", 4))
	{
		ImGui::TableSetupColumn("Filename");
		ImGui::TableSetupColumn("Type");
		ImGui::TableSetupColumn("Size");
		ImGui::TableSetupColumn("##Buttons");
		ImGui::TableHeadersRow();

		for (auto& p : fs::recursive_directory_iterator(this->selectedFilepath))
		{
			std::string pathString = p.path().filename().string();
			if (!LString::FuzzyMatch(searchBuffer, pathString.c_str()))
				continue;

			EAssetType type = LFileOperations::GetFileType(pathString);
			size_t size = fs::file_size(p);
			if (type == EAssetType::Meta || type == EAssetType::Directory)
				continue;

			if (!fileMask.CompareFile(FFileCategory(type, false)))
				continue;

			ImGui::TableNextColumn();
			ImGui::Text(pathString.c_str());

			ImGui::TableNextColumn();
			ImGui::Text(LFileOperations::AssetTypeToString(type).c_str());

			ImGui::TableNextColumn();
			ImGui::Text(LFileOperations::BytesToString(size, 2).c_str());

			ImGui::TableNextColumn();
			if (ImGui::Button("Go-To"))
			{
				memset(searchBuffer, 0, 64);
				this->selectedFilepath = p.path().parent_path().string();
				LFileOperations::CorrectFilepath(this->selectedFilepath);
			}
		}

		ImGui::EndTable();
	}
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
	if (openFolderMenu)
	{
		ImGui::OpenPopup("Create Folder");
		openFolderMenu = false;
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

/*
Audio - Audio Viewer (To-Do)
Animation - Animation Viewer (To-Do)
Cpp/H - Visual Studio
Data - Excel
Font - Font Viewer (To-Do)
Image - Image Viewer
Markup - ?
Material - Material Viewer
Mesh - Mesh Viewer
Meta - ?
NonEngineCode - Visual Studio
Particle - Particle Viewer (To-Do)
Prefab - ?
Shader - Shader Graph/Visual Studio
Scene - Open Scene
Text - Visual Studio
Video - ?
*/

void FileView::OpenFile(const std::string & str, EAssetType type)
{
	switch (type)
	{
	case EAssetType::Font:
	{
		FontViewer* fontViewer = (FontViewer*)EditorApplication::AddModule(new FontViewer());
		fontViewer->loadedRef = FontManager::LoadFont(str);
	}
	break;
	case EAssetType::Image:
	{
		ImageViewer* imageViewer = (ImageViewer*)EditorApplication::AddModule(new ImageViewer());
		imageViewer->loadedRef = TextureManager::LoadTexture(str);
	}
	break;
	case EAssetType::InputMap:
	{
		InputMapViewer* inputMapViewer = (InputMapViewer*)EditorApplication::AddModule(new InputMapViewer());
		inputMapViewer->Load(str);
	}
	break;
	case EAssetType::Material:
	{
		MaterialEditor* materialEditor = (MaterialEditor*)EditorApplication::AddModule(new MaterialEditor());
		materialEditor->SetMaterial(str);
	}
	break;
	case EAssetType::Mesh:
	{
		MeshViewer* meshViewer = (MeshViewer*)EditorApplication::AddModule(new MeshViewer());
		meshViewer->loadedRef = MeshManager::LoadMesh(str);
	}
	break;
	case EAssetType::Scene:
	{
		// Add stuff here
	}
	break;
	}
}

void FileView::Display()
{
	PROFILE_SCOPE("FileView::Display");

	DisplayMenuBar();
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
	case EAssetType::Font: return "EXPERIO_FONT";
	case EAssetType::Image: return "EXPERIO_IMAGE";
	case EAssetType::Material: return "EXPERIO_MATERIAL";
	case EAssetType::Mesh: return "EXPERIO_MESH";
	case EAssetType::Text: return "EXPERIO_TEXT";
	}
	return "EXPERIO_FILE";
}

bool FileView::IsAssetLoaded(const std::string& filepath, EAssetType type)
{
	switch (type)
	{
	case EAssetType::Mesh:
		return MeshManager::IsMeshLoaded(filepath);
	case EAssetType::Image:
		return TextureManager::IsTextureLoaded(filepath);
	case EAssetType::Font:
		return FontManager::IsFontLoaded(filepath);
	case EAssetType::Data:
		return DataManager::IsDataLoaded(filepath);
	}
	return false;
}