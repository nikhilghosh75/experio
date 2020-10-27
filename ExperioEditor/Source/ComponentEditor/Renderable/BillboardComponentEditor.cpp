#include "BillboardComponentEditor.h"
#include "Runtime/Rendering/ImGui/LImGui.h"

void BillboardEditor::Display(Component * billboardComponent)
{
	Billboard* billboard = (Billboard*)billboardComponent;
	
	LImGui::DisplayTextureAsset(billboard->billboardTexture, "Texture");
	LImGui::DisplayEnum<EBillboardSizeType>(billboard->sizeType, "Size Type");
	LImGui::DisplayEnum<EBilboardOrientation>(billboard->orientation, "Orientation");
	LImGui::DisplayVector2(billboard->billboardSize, "Size");
}
