#include "FontViewer.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Debug/Profiler.h"
#include "Runtime/Files/Font/LFontOperations.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "Runtime/Rendering/Managers/FontManager.h"
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

void FontViewer::DisplayVariants()
{
	for (size_t i = 0; i < loadedRef->variants.size(); i++)
	{
		uint16_t variantId = loadedRef->variants[i].dataIndex;
		FontRef variantRef = FontManager::GetFont(variantId);
		EFontType variantType = loadedRef->variants[i].type;
		std::string variantTypeStr = LFontOperations::FontTypeToString(variantType);

		LImGui::DisplayFontAsset(variantRef, variantTypeStr);
		loadedRef->variants[i].dataIndex = variantRef.fontID;
		ImGui::SameLine();
		ImGui::PushID(i + 6);
		if (ImGui::Button("-", ImVec2(20, 0)))
			Experio::Algorithm::RemoveAt(loadedRef->variants, i);
		ImGui::PopID();
	}

	if (ImGui::Button("+"))
	{
		ImGui::OpenPopup("##AddVariant");
	}

	if (ImGui::BeginPopup("##AddVariant"))
	{
		if (ImGui::MenuItem("Normal"))
			loadedRef->variants.emplace_back(EFontType::Normal);
		if (ImGui::MenuItem("Bold"))
			loadedRef->variants.emplace_back(EFontType::Normal);
		if (ImGui::MenuItem("Italic"))
			loadedRef->variants.emplace_back(EFontType::Italics);
		if (ImGui::MenuItem("Bold Italic"))
			loadedRef->variants.emplace_back(EFontType::BoldItalics);
		
		ImGui::EndPopup();
	}
}

FontViewer::FontViewer()
{
	this->name = "Font Viewer";
	this->category = EEditorModuleCategory::Viewer;
	this->filepath = "";
}

void FontViewer::Display()
{
	PROFILE_SCOPE("FontViewer::Display");

	if (loadedRef.IsNull())
	{
		return;
	}

	if (ImGui::BeginTabBar("##Menu"))
	{
		if (ImGui::BeginTabItem("Stats"))
		{
			DisplayStats();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Variants"))
		{
			DisplayVariants();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

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
