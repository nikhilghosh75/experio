#include "LImGui.h"
#include "../Debug/Debug.h"
#include "../Containers/LStandard.h"

uint64_t LImGui::DisplayBitmask(std::string name, std::vector<std::string>& names, bool* selected)
{
	uint64_t currentMask = 0;

	std::string title = "None";
	int amountSelected = 0;

	for (int i = 0; i < names.size(); i++)
	{
		if (selected[i])
		{
			title = names[i];
			amountSelected++;
			currentMask = currentMask | (1 << i);
		}
	}

	if (amountSelected > 1)
	{
		if (amountSelected == names.size())
		{
			title = "All";
		}
		else
		{
			title = "Multiple";
		}
	}

	if (ImGui::BeginCombo(name.c_str(), title.c_str()))
	{
		for (int i = 0; i < names.size(); i++)
		{
			Debug::Log(names[i]);
			if (ImGui::Selectable(names[i].c_str(), &(selected[i]), ImGuiSelectableFlags_DontClosePopups))
			{
				currentMask = currentMask | (1 << i);
			}
			else
			{
				currentMask = currentMask & (~(1 << i));
			}
		}
		ImGui::EndCombo();
	}
	return currentMask;
}

void LImGui::DisplaySubTree(TTypedTreeNode<std::string>* subtree, std::string name)
{
	if (subtree->children.size() == 0)
	{
		ImGui::Text(subtree->object.c_str());
	}
	else
	{
		if (ImGui::TreeNode(name.c_str(), subtree->object.c_str()))
		{
			for (int i = 0; i < subtree->children.size(); i++)
			{
				DisplaySubTree(subtree->children[i], name + std::to_string(i));
			}
			ImGui::TreePop();
		}
	}
}

void LImGui::DisplaySubTree(TTypedTreeNode<std::string>* subtree, std::string name, std::string& selectedItem)
{
	if (subtree->children.size() == 0)
	{
		if (ImGui::Selectable(subtree->object.c_str(), selectedItem == subtree->object))
		{
			selectedItem = subtree->object;
		}
	}
	else
	{
		ImGuiTreeNodeFlags_ flags = selectedItem == subtree->object ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
		if (ImGui::TreeNodeEx(subtree->object.c_str(), flags))
		{
			if (ImGui::IsItemClicked())
			{
				selectedItem = subtree->object;
			}

			for (int i = 0; i < subtree->children.size(); i++)
			{
				DisplaySubTree(subtree->children[i], name + std::to_string(i), selectedItem);
			}
			ImGui::TreePop();
		}
	}
}

void LImGui::DisplaySubTree(TTypedTreeNode<std::string>* subtree, std::string name, std::vector<std::string>& selectedItems)
{
	bool isSelected = LStandard::ExistsInVector(selectedItems, subtree->object);
	if (subtree->children.size() == 0)
	{
		if (ImGui::Selectable(subtree->object.c_str(), isSelected))
		{
			if (!isSelected)
			{
				selectedItems.push_back(subtree->object);
			}
			else
			{
				LStandard::RemoveElement(selectedItems, subtree->object);
			}
		}
	}
	else
	{
		ImGuiTreeNodeFlags_ flags = isSelected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
		if (ImGui::TreeNodeEx(subtree->object.c_str(), flags))
		{
			if (ImGui::IsItemClicked())
			{
				if (isSelected)
				{
					LStandard::RemoveElement(selectedItems, subtree->object);
				}
				else
				{
					selectedItems.push_back(subtree->object);
				}
			}

			for (int i = 0; i < subtree->children.size(); i++)
			{
				DisplaySubTree(subtree->children[i], name + std::to_string(i), selectedItems);
			}
			ImGui::TreePop();
		}
	}
}

void LImGui::DisplayTree(TTypedTree<std::string>* tree, std::string name)
{
	if (!ImGui::TreeNode(name.c_str()))
	{
		return;
	}
	
	TTypedTreeNode<std::string>* root = tree->GetRoot();
	
	for (int i = 0; i < root->children.size(); i++)
	{
		DisplaySubTree(root->children[i], name + std::to_string(i));
	}
	ImGui::TreePop();
}

void LImGui::DisplayTree(TTypedTree<std::string>* tree, std::string name, std::string& selectedItem)
{
	ImGuiTreeNodeFlags_ flags = selectedItem == tree->GetRoot()->object ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
	if (!ImGui::TreeNodeEx(name.c_str(), flags))
	{
		return;
	}

	TTypedTreeNode<std::string>* root = tree->GetRoot();

	for (int i = 0; i < root->children.size(); i++)
	{
		DisplaySubTree(root->children[i], name + std::to_string(i), selectedItem);
	}
	ImGui::TreePop();
}

void LImGui::DisplayTree(TTypedTree<std::string>* tree, std::string name, std::vector<std::string>& selectedItems)
{
	bool isSelected = LStandard::ExistsInVector(selectedItems, tree->GetRootObject());
	ImGuiTreeNodeFlags_ flags = isSelected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
	if (!ImGui::TreeNodeEx(name.c_str(), flags))
	{
		return;
	}

	TTypedTreeNode<std::string>* root = tree->GetRoot();

	for (int i = 0; i < root->children.size(); i++)
	{
		DisplaySubTree(root->children[i], name + std::to_string(i), selectedItems);
	}
	ImGui::TreePop();
}

template<typename T>
void LImGui::DisplaySubtreeOfType(TTypedTreeNode<T>* subtree, std::string name, std::vector<T>& selectedItems, std::function<std::string(T)> convertFunc)
{
	bool isSelected = ExistsInVector(selectedItems, subtree->object);
	if (subtree->children.size() == 0)
	{
		if (ImGui::Selectable(convertFunc(subtree->object).c_str(), isSelected))
		{
			if (!isSelected)
			{
				selectedItems.push_back(subtree->object);
			}
			else
			{
				RemoveElement(selectedItems, subtree->object);
			}
		}
	}
	else
	{
		ImGuiTreeNodeFlags_ flags = isSelected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
		if (ImGui::TreeNodeEx(subtree->object.c_str(), flags))
		{
			if (ImGui::IsItemClicked())
			{
				if (isSelected)
				{
					LStandard::RemoveElement(selectedItems, subtree->object);
				}
				else
				{
					selectedItems.push_back(subtree->object);
				}
			}

			for (int i = 0; i < subtree->children.size(); i++)
			{
				DisplaySubtreeOfType(subtree->children[i], name + std::to_string(i), selectedItems, convertFunc);
			}
			ImGui::TreePop();
		}
	}
}

template<typename T>
void LImGui::DisplayTreeOfType(TTypedTree<T>* tree, std::string name, std::vector<T>& selectedItems, std::function<std::string(T)> convertFunc)
{
	bool isSelected = LStandard::ExistsInVector(selectedItems, tree->GetRootObject());
	ImGuiTreeNodeFlags_ flags = isSelected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None;
	if (!ImGui::TreeNodeEx(name.c_str(), flags))
	{
		return;
	}

	TTypedTreeNode<T>* root = tree->GetRoot();

	for (int i = 0; i < root->children.size(); i++)
	{
		DisplaySubtreeOfType(root->children[i], name + std::to_string(i), selectedItems, convertFunc);
	}
	ImGui::TreePop();
}
