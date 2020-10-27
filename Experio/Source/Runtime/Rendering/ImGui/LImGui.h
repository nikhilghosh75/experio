#pragma once
#include "imgui.h"
#include "../../Containers/TTypedTree.h"
#include <string>
#include "../../Math/FVector2.h"
#include "../../Math/FVector3.h"
#include "../../Math/FVector4.h"
#include "../../Math/FQuaternion.h"
#include "../../UI/UIColorPalettes.h"
#include "../../../ThirdParty/Magic Enum/magic_enum.hpp"
#include "../../../ThirdParty/Nameof/nameof.hpp"

class MeshRef;
class TextureRef;

class LImGui
{
public:
	static uint64_t DisplayBitmask(std::string name, std::vector<std::string>& names, bool* selected);

	static void DisplayBool(bool& boolean, std::string name);

	template<typename T>
	static void DisplayEnum(T& currentEnum, std::string name);

	static void DisplayMeshAsset(MeshRef& ref, std::string name);

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