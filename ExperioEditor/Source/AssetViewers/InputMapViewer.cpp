#include "InputMapViewer.h"
#include "../Core/FileDialog.h"
#include "Runtime/Input/InputMapReader.h"
#include "Runtime/Files/LFileOperations.h"

InputMapViewer::InputMapViewer()
{
	this->category = EEditorModuleCategory::Viewer;
	this->name = "Input Map Viewer";

	loaded = false;
}

void InputMapViewer::Display()
{
	if (!loaded)
		DisplayEmpty();
	else
		DisplayInputMap();
}

void InputMapViewer::Load(const std::string& filepath)
{
	this->filepath = filepath;
	this->mapName = LFileOperations::StripFilenameAndExt(filepath);
	this->currentMap = InputMapReader::ReadInputMap(filepath);
	this->loaded = true;
}

void InputMapViewer::DisplayEmpty()
{
	if (ImGui::Button("Load Input Map"))
	{
		FFileDialogInfo info = FileDialog::OpenFile("Experio Input Map (*.pbipmap)\0*.pbipmap\0");
		if (info.IsValid())
			Load(info.filename);
	}
}

void InputMapViewer::DisplayInputMap()
{
	ImGui::Text(this->mapName.c_str());
}
