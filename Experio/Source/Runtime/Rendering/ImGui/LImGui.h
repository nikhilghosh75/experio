#pragma once
#include "imgui.h"
#include "../Renderer.h"
#include "../../Containers/THashtable.h"
#include "../../Containers/TTypedTree.h"
#include <string>
#include "../../Files/FileRef.h"
#include "../../Files/TextRef.h"
#include "../../Math/Bezier.h"
#include "../../Math/FBox.h"
#include "../../Math/FRect.h"
#include "../../Math/FVector2.h"
#include "../../Math/FVector3.h"
#include "../../Math/FVector4.h"
#include "../../Math/FQuaternion.h"
#include "../../UI/UIColorPalettes.h"
#include "../../../ThirdParty/Magic Enum/magic_enum.hpp"
#include "../../../ThirdParty/Nameof/nameof.hpp"

class FontRef;
class MeshRef;
class TextureRef;

typedef int ImGuiFilterComboFlags; // -> enum ImGuiFilterComboFlags_   // Flags: for FilterCombo

struct ImGuiFilterComboState
{
	int  activeIdx = 0;
	bool selectionChanged = false;
};

struct ImGuiBezierCurveState
{
	float startX;
	float startY;
	float endX;
	float endY;
};

class LImGui
{
public:
	static uint64_t DisplayBitmask(std::string name, const std::vector<std::string>& names, bool* selected);

	static void DisplayBool(bool& boolean, std::string name);

	static void DisplayBox(FBox& box, std::string name);

	static void DisplayColorSmall(ImU32 color32, std::string name);

	static void DisplayCurve(const char* label, Bezier& bezier, ImGuiBezierCurveState& bezierState);

	template<typename T>
	static void DisplayEnum(T& currentEnum, std::string name);

	static void DisplayFileAsset(FileRef& ref, std::string name);

	static void DisplayFontAsset(FontRef& ref, std::string name);

	static void DisplayLayer(uint8_t& layer, const THashtable<uint16_t, std::string>& layerTable);

	static void DisplayMaterial(Material* material, const std::string& name);

	static void DisplayMeshAsset(MeshRef& ref, const std::string& name);

	static void DisplayQuaternion(FQuaternion& quat, const std::string& name);

	static void DisplayRect(FRect& rect, const std::string& name);

	static bool DisplayString(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);

	static void DisplayTag(uint16_t& tag, const THashtable<uint16_t, std::string>& tagTable);

	static void DisplayTextAsset(TextRef& ref, const std::string& name);

	static void DisplayTexture(TextureRef& ref, const std::string& name, unsigned int width = 100, unsigned int height = 100);

	static void DisplayTextureAsset(TextureRef& ref, std::string name);

	static void DisplaySubTree(TTypedTreeNode<std::string>* subtree, std::string name);
	static void DisplaySubTree(TTypedTreeNode<std::string>* subtree, std::string name, std::string& selectedItem); // For Single Select Tree
	static void DisplaySubTree(TTypedTreeNode<std::string>* subtree, std::string name, std::vector<std::string>& selectedItems); // For Multi Select Tree

	static void DisplayTree(TTypedTree<std::string>* tree, std::string name);
	static void DisplayTree(TTypedTree<std::string>* tree, std::string name, std::string& selectedItem); // For Single Select Tree
	static void DisplayTree(TTypedTree<std::string>* tree, std::string name, std::vector<std::string>& selectedItems); // For Multi Select Tree

	template<typename T>
	static void DisplaySubtreeOfType(TTypedTreeNode<T>* tree, std::string name, std::vector<T>& selectedItems, std::function<std::string(T)> convertFunc);

	template<typename T>
	static void DisplayTreeOfType(TTypedTree<T>* tree, std::string name, std::vector<T>& selectedItems, std::function<std::string(T)> convertFunc);

	static void DisplayTransform(FVector3& position, FQuaternion& rotation, FVector3& scale);

	static void DisplayVector2(FVector2& V, const std::string& name, const FVector2& resetValue = FVector2(0, 0),
		const FButtonColorPalette& xColorPalette = FButtonColorPalette::redPalette, const FButtonColorPalette& yColorPalette = FButtonColorPalette::greenPalette);

	static void DisplayVector3(FVector3& V, const std::string& name, const FVector3& resetValue = FVector3(0, 0, 0), 
		const FButtonColorPalette& xColorPalette = FButtonColorPalette::redPalette, const FButtonColorPalette& yColorPalette = FButtonColorPalette::greenPalette, 
		const FButtonColorPalette& zColorPalette = FButtonColorPalette::bluePalette);

	static void DisplayVector4(FVector4& V, const std::string& name, const FVector4& resetValue = FVector4(0, 0, 0, 0),
		const FButtonColorPalette& xColorPalette = FButtonColorPalette::redPalette, const FButtonColorPalette& yColorPalette = FButtonColorPalette::greenPalette, 
		const FButtonColorPalette& zColorPalette = FButtonColorPalette::bluePalette, const FButtonColorPalette& wColorPalette = FButtonColorPalette::yellowPalette);

	static bool FilterCombo(const char* label, char* buffer, int bufferlen, const char** hints, int num_hints, ImGuiFilterComboState& s, ImGuiFilterComboFlags flags = 0);
};

template<typename T>
void LImGui::DisplayEnum(T& currentEnum, std::string name)
{
	size_t enumCount = magic_enum::enum_count<T>();
	auto& enumNames = magic_enum::enum_names<T>();
	auto& enumValues = magic_enum::enum_values<T>();

	std::string currentEnumName = magic_enum::enum_name(currentEnum).data();

	if (ImGui::BeginCombo(name.c_str(), currentEnumName.c_str()))
	{
		for (int i = 0; i < enumCount; i++)
		{
			if (ImGui::Selectable(enumNames[i].data(), enumNames[i] == currentEnumName, ImGuiSelectableFlags_DontClosePopups))
			{
				currentEnum = enumValues[i];
			}
		}
		ImGui::EndCombo();
	}
}

enum ImGuiFilterComboFlags_
{
	ImGuiFilterComboFlags_None = 0,
	ImGuiFilterComboFlags_HeightSmall = 1 << 1, // Only 4 items
	ImGuiFilterComboFlags_HeightRegular = 1 << 2 // Only 8 items
};