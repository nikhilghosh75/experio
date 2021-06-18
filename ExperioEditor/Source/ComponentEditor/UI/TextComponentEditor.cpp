#include "TextComponentEditor.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

void TextComponentEditor::Display(Component* component)
{
	TextComponent* textComponent = (TextComponent*)component;

	ImGui::DragFloat("Margins", &textComponent->margins, 10, 0, 100);
	ImGui::DragInt("FontSize", &textComponent->fontSize, 2, 2, 480);
	LImGui::DisplayFontAsset(textComponent->font, "Font");
	LImGui::DisplayString("Text", &textComponent->text);
	ImGui::ColorEdit4("Color", (float*)&textComponent->color, ImGuiColorEditFlags_Float);
	LImGui::DisplayEnum<EHorizontalWrapMode>(textComponent->horizontalWrapMode, "Horizontal Wrap");
	LImGui::DisplayEnum<EVerticalWrapMode>(textComponent->verticalWrapMode, "Vertical Wrap");
	LImGui::DisplayEnum<EHorizontalAlignment>(textComponent->horizontalAlignment, "Horizontal Alignment");
	LImGui::DisplayEnum<EVerticalAlignment>(textComponent->verticalAlignment, "Vertical Alignment");
	ImGui::DragFloat("Spacing", &textComponent->spacing, 1, 0, 40);

	if (ImGui::Button("Normal"))
		textComponent->SetTextType(EFontType::Normal);
	else if (ImGui::Button("Bold"))
		textComponent->SetTextType(EFontType::Bold);
	else if (ImGui::Button("Italics"))
		textComponent->SetTextType(EFontType::Italics);
	else if (ImGui::Button("Bold Italics"))
		textComponent->SetTextType(EFontType::BoldItalics);
}