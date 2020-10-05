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

	void DisplayTree();
	void DisplayContents();

	std::string GetSelectedFilepath(TTypedTreeNode<std::string>* selectedNode);
public:
	FileView();

	virtual void Display() override;
};