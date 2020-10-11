#pragma once
#include "imgui.h"
#include "../Containers/TTypedTree.h"
#include <string>

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
};
