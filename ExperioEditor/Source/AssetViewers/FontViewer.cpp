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

	ImGui::Text(std::to_string(uvPosition.x).c_str());
	ImGui::SameLine();
	ImGui::Text(std::to_string(uvPosition.y).c_str());

	ImVec2 currentSize = ImGui::GetContentRegionAvail();
	ImVec2 imagePos = ImGui::GetCursorScreenPos();
	ImGui::Image((void*)loadedRef->fontTexture->GetRendererID(), currentSize);

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();

		ImGuiIO& io = ImGui::GetIO();

		uvPosition = ImVec2(io.MousePos.x - imagePos.x, io.MousePos.y - imagePos.y);

		float zoom = 4.0f;
		float imageWidth = loadedRef->fontTexture->GetWidth();
		float imageHeight = loadedRef->fontTexture->GetHeight();
		if (uvPosition.x < 0.0f) {uvPosition.x = 0.0f; }
		else if (uvPosition.x > currentSize.x) { uvPosition.x = currentSize.x; }
		if (uvPosition.y < 0.0f) { uvPosition.y = 0.0f; }
		else if (uvPosition.y > currentSize.y) { uvPosition.y = currentSize.y; }
		uvPosition.x /= currentSize.x;
		uvPosition.y /= currentSize.y;

		ImGui::Text(std::to_string(LFontOperations::GetCharCodeOfUV(*loadedRef.fontData, uvPosition)).c_str());

		ImGui::EndTooltip();
	}
}
