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

	TTypedTree<std::string>* directories;

	// Change Later
	bool filesSelected[18];

	void DisplayCreateMenu();
	void DisplayImportMenu();

	void DisplayContextMenu();
	void DisplayTree();
	void DisplayContents();

	void OpenCreateMenus();

	std::string GetSelectedFilepath(TTypedTreeNode<std::string>* selectedNode);

	void OpenFile(const std::string& str, EAssetType type);
public:
	static FileView* fileView;

	FileView();

	~FileView();

	virtual void Display() override;

	virtual void HandleInput() override;

	void Reload();

	std::string GetSelectedItem() const { return this->selectedItem; }
	std::string GetSelectedFilepath() const { return this->selectedFilepath; }

	static std::string GetDragDropTypeFromAssetType(EAssetType type);

	static bool IsAssetLoaded(const std::string& filepath, EAssetType type);
};