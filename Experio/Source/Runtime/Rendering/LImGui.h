#pragma once
#include "imgui.h"
#include "../Containers/TTypedTree.h"
#include <string>
#include "../Math/FVector3.h"
#include "../Math/FVector4.h"
#include "../Math/FQuaternion.h"
#include "../UI/UIColorPalettes.h"

class LImGui
{
public:
	static uint64_t DisplayBitmask(std::string name, std::vector<std::string>& names, bool* selected);

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

	static void DisplayVector3(FVector3& V, const std::string& name, const FVector3& resetValue = FVector3(0, 0, 0), 
		const FButtonColorPalette& xColorPalette = FButtonColorPalette::redPalette, const FButtonColorPalette& yColorPalette = FButtonColorPalette::greenPalette, 
		const FButtonColorPalette& zColorPalette = FButtonColorPalette::bluePalette);

	static void DisplayVector4(FVector4& V, const std::string& name, const FVector4& resetValue = FVector4(0, 0, 0, 0),
		const FButtonColorPalette& xColorPalette = FButtonColorPalette::redPalette, const FButtonColorPalette& yColorPalette = FButtonColorPalette::greenPalette, 
		const FButtonColorPalette& zColorPalette = FButtonColorPalette::bluePalette, const FButtonColorPalette& wColorPalette = FButtonColorPalette::yellowPalette);
};
