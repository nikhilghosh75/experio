#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Containers/TTypedTree.h"
#include "Runtime/Files/Filemask.h"
#include <string>

class FileView : public EditorModule
{
	std::string assetFilePath;
	std::string selectedItem = "Assets";
	std::string selectedFilepath = "";

	// Change Later
	bool filesSelected[17];

	void DisplayCreateMenu();
	void DisplayImportMenu();

	void DisplayContextMenu();
	void DisplayTree();
	void DisplayContents();

	void OpenCreateMenus();

	std::string GetSelectedFilepath(TTypedTreeNode<std::string>* selectedNode);
public:
	FileView();

	virtual void Display() override;

	virtual void HandleInput() override;

	static std::string GetDragDropTypeFromAssetType(EAssetType type);

	static bool IsAssetLoaded(const std::string& filepath, EAssetType type);
};