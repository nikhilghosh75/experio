#include "ImageViewer.h"
#include "Runtime/Files/Images/LImageOperations.h"
#include <sstream>

void ImageViewer::DisplayStats()
{
	std::string filepath = TextureManager::GetNameOfTexture(loadedRef);
	ImGui::Text(filepath.c_str());

	unsigned int width, height;
	width = loadedRef->GetWidth();
	height = loadedRef->GetHeight();
	std::stringstream ss;
	ss << width << "x" << height;
	ImGui::Text(ss.str().c_str());

	ss.clear();
	ss << "Size: " << LImageOperations::SizeOfImage(loadedRef) << " bytes";
	ImGui::Text(ss.str().c_str());
}

ImageViewer::ImageViewer()
{
	this->name = "Image Viewer";
	this->category = EEditorModuleCategory::Viewer;
}

void ImageViewer::Display()
{
	if (loadedRef.IsNull())
	{
		return;
	}

	DisplayStats();

	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 currentSize = ImGui::GetWindowSize();
	currentSize = ImVec2(currentSize.x - 12, currentSize.y - 145); // Change Later

	ImGui::Image((void*)loadedRef->GetRendererID(), currentSize, ImVec2(0, 1), ImVec2(1, 0));
}
