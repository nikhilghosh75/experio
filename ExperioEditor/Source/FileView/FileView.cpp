#include "FileView.h"
#include <filesystem>
#include "Runtime/Debug/Debug.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Rendering/LImGui.h"
#include "Runtime/Math/LMath.h"
namespace fs = std::filesystem;

FileView::FileView()
{
	this->name = "Files";
	this->category = EEditorModuleCategory::Core;

	this->assetFilePath = "C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets";

	for (int i = 0; i < 17; i++)
	{
		this->filesSelected[i] = true;
	}
}

void FileView::DisplayTree()
{
	ImGui::BeginChild("Directories", ImVec2(200, 0), true);

	TTypedTree<std::string>* directories = LFileOperations::CreateFileNamesTree(this->assetFilePath, EFileTreeOptions::DisplayDirectories);
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

	delete directories;
}

void FileView::DisplayContents()
{
	FRect rect = GetWindowRect();
	ImGui::SameLine();
	ImGui::BeginChild("Contents", ImVec2(rect.GetWidth() - 300, 0), true);

	static std::vector<std::string> fileTypes = { "Audio", "Animation", "Code",
		"Data", "Font", "Image", "H", "Material", "Mesh", "Meta", "NonEngineCode", 
		"Particle", "Prefab", "Shader", "Scene", "Text","Video" 
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
					// Add Mesh View
					break;
				case EAssetType::Image:
					// Add Image View
					break;
				}
			}
		}
	}

	ImGui::EndChild();
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
	DisplayTree();
	DisplayContents();
}