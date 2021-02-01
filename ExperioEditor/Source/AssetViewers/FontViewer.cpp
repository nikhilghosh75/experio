#include "FontViewer.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Files/Font/LFontOperations.h"
#include <sstream>

void FontViewer::DisplayStats()
{
	if (filepath.size() < 2)
	{
		filepath = FontManager::GetNameOfFont(loadedRef).substr(3);
	}
	ImGui::Text(filepath.c_str());

	unsigned int numCharacters = loadedRef->characters.size();
	std::stringstream ss;
	ss << "Characters: " << numCharacters;
	ImGui::Text(ss.str().c_str());

	ss.str("");
	ss.clear();
	size_t sizeOfFont = LFontOperations::SizeOf(*loadedRef.fontData);
	ss << "Size: " << LString::NumberWithCommas(sizeOfFont) << " bytes";
	ImGui::Text(ss.str().c_str());
}

FontViewer::FontViewer()
{
	this->name = "Font Viewer";
	this->category = EEditorModuleCategory::Viewer;
	this->filepath = "";
}

void FontViewer::Display()
{
	if (loadedRef.IsNull())
	{
		return;
	}

	DisplayStats();

	ImVec2 currentSize = ImGui::GetContentRegionAvail();
	ImVec2 imagePos = ImGui::GetCursorScreenPos();
	ImGui::Image((void*)loadedRef->fontTexture->GetRendererID(), currentSize);

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();

		ImGuiIO& io = ImGui::GetIO();

		ImVec2 uvPosition = ImVec2(io.MousePos.x - imagePos.x, io.MousePos.y - imagePos.y);

		float zoom = 4.0f;
		float imageWidth = loadedRef->fontTexture->GetWidth();
		float imageHeight = loadedRef->fontTexture->GetHeight();
		if (uvPosition.x < 0.0f) {uvPosition.x = 0.0f; }
		else if (uvPosition.x > imageWidth) { uvPosition.x = imageWidth; }
		if (uvPosition.y < 0.0f) { uvPosition.y = 0.0f; }
		else if (uvPosition.y > imageHeight) { uvPosition.y = imageHeight; }
		uvPosition.x /= imageWidth;
		uvPosition.y /= imageHeight;

		ImGui::Text(std::to_string(LFontOperations::GetCharCodeOfUV(*loadedRef.fontData, uvPosition)).c_str());

		ImGui::EndTooltip();
	}
}
