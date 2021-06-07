#include "ImageViewer.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Debug/Profiler.h"
#include "Runtime/Files/Images/LImageOperations.h"
#include "Runtime/Rendering/Renderer.h"
#include <sstream>

void ImageViewer::DisplayStats()
{
	PROFILE_SCOPE("ImageViewer::DisplayStats");

	if (filepath.size() < 2)
	{
		filepath = TextureManager::GetNameOfTexture(loadedRef).substr(3);
	}
	ImGui::Text(filepath.c_str());

	unsigned int width, height;
	width = loadedRef->GetWidth();
	height = loadedRef->GetHeight();
	std::stringstream ss;
	ss << width << "x" << height;
	ImGui::Text(ss.str().c_str());

	ss.str("");
	ss.clear();
	size_t sizeOfImage = LImageOperations::SizeOfImage(loadedRef);
	ss << "Size: " << LString::NumberWithCommas(sizeOfImage) << " bytes";
	ImGui::Text(ss.str().c_str());
}

ImageViewer::ImageViewer()
{
	this->name = "Image Viewer";
	this->category = EEditorModuleCategory::Viewer;
	this->filepath = "";
}

void ImageViewer::Display()
{
	PROFILE_SCOPE("ImageViewer::Display");
	if (loadedRef.IsNull())
	{
		return;
	}

	DisplayStats();

	ImVec2 currentSize = ImGui::GetContentRegionAvail();
	ImGui::Image((void*)loadedRef->GetRendererID(), currentSize);
}
