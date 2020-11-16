#include "LImGui.h"
#include "../../Debug/Debug.h"
#include "../../Containers/Algorithm.h"
#include "../../Files/LFileOperations.h"
#include "../Managers/MeshManager.h"
#include "../Managers/TextureManager.h"
#include "imgui_internal.h"

using namespace Experio;

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

void LImGui::DisplayBool(bool& boolean, std::string name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	ImGui::Checkbox(("##" + name).c_str(), &boolean);

	ImGui::Columns(1);
	ImGui::PopID();
}

void LImGui::DisplayLayer(uint8_t& layer, const THashtable<uint16_t, std::string>& layerTable)
{
	uint16_t layer16 = layer;
	const std::string layerName = layerTable.Get(layer);

	if (ImGui::BeginCombo("Layer", layerName.c_str()))
	{
		layerTable.ForEach([&layer16](const uint16_t& index, const std::string& name) {
			bool isSelected = index == layer16;
			if (ImGui::Selectable(name.c_str(), &isSelected, ImGuiSelectableFlags_DontClosePopups))
			{
				uint16_t temp = index;
				layer16 = temp;
			}
		});
		layer = layer16;
		ImGui::EndCombo();
	}
}

void LImGui::DisplayMeshAsset(MeshRef & ref, std::string name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	std::string meshFileName = MeshManager::GetNameOfMesh(ref);
	std::string meshName = LFileOperations::StripFilename(meshFileName);
	ImGui::Text(meshName.c_str());

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_MESH"))
		{
			char* meshName = (char*)payload->Data;
			ref = MeshManager::LoadMesh(meshName);
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Switch"))
	{
		// Add Later
	}

	ImGui::Columns(1);
	ImGui::PopID();
}

void LImGui::DisplayTag(uint16_t& tag, const THashtable<uint16_t, std::string>& tagTable)
{
	const std::string tagName = tagTable.Get(tag);
	
	if (ImGui::BeginCombo("Tag", tagName.c_str()))
	{
		tagTable.ForEach([&tag](const uint16_t& index, const std::string& name) {
			bool isSelected = index == tag;
			if (ImGui::Selectable(name.c_str(), &isSelected, ImGuiSelectableFlags_DontClosePopups))
			{
				uint16_t temp = index;
				tag = temp;
			}
		});
		ImGui::EndCombo();
	}
}

void LImGui::DisplayTextureAsset(TextureRef & ref, std::string name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	std::string meshFileName = TextureManager::GetNameOfTexture(ref);
	std::string meshName = LFileOperations::StripFilename(meshFileName);
	ImGui::Text(meshName.c_str());

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_IMAGE"))
		{
			char* imageName = (char*)payload->Data;
			ref = TextureManager::LoadTexture(imageName);
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Switch"))
	{
		// Add Later
	}

	ImGui::Columns(1);
	ImGui::PopID();
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
	bool isSelected = Algorithm::ExistsIn(selectedItems, subtree->object);
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
				Algorithm::RemoveElement(selectedItems, subtree->object);
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
					Algorithm::RemoveElement(selectedItems, subtree->object);
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
	bool isSelected = Algorithm::ExistsIn(selectedItems, tree->GetRootObject());
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

void LImGui::DisplayTransform(FVector3& position, FQuaternion& rotation, FVector3& scale)
{
	DisplayVector3(position, "Position");

	FVector4 rotationV = FVector4(rotation.w, rotation.x, rotation.y, rotation.z);
	DisplayVector4(rotationV, "Rotation", FVector4(1, 0, 0, 0));
	rotation = FQuaternion(rotationV.x, rotationV.y, rotationV.z, rotationV.w);

	DisplayVector3(scale, "Scale", FVector3(1, 1, 1));
}

void LImGui::DisplayVector2(FVector2 & V, const std::string & name, const FVector2 & resetValue, const FButtonColorPalette & xColorPalette, const FButtonColorPalette & yColorPalette)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = ImVec2(lineHeight + 3.f, lineHeight);

	ImGui::PushStyleColor(ImGuiCol_Button, xColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, xColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, xColorPalette.activeColor);

	if (ImGui::Button("X", buttonSize))
	{
		V.x = resetValue.x;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &V.x, 0.1f, 0.0f, 0.0f, "%.3f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, yColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, yColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, yColorPalette.activeColor);

	if (ImGui::Button("Y", buttonSize))
	{
		V.y = resetValue.y;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &V.y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
}

void LImGui::DisplayVector3(FVector3& V, const std::string & name, const FVector3 & resetValue, const FButtonColorPalette& xColorPalette, const FButtonColorPalette& yColorPalette, const FButtonColorPalette& zColorPalette)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = ImVec2(lineHeight + 3.f, lineHeight);

	ImGui::PushStyleColor(ImGuiCol_Button, xColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, xColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, xColorPalette.activeColor);

	if (ImGui::Button("X", buttonSize))
	{
		V.x = resetValue.x;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &V.x, 0.1f, 0.0f, 0.0f, "%.3f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, yColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, yColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, yColorPalette.activeColor);

	if (ImGui::Button("Y", buttonSize))
	{
		V.y = resetValue.y;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &V.y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, zColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, zColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, zColorPalette.activeColor);

	if (ImGui::Button("Z", buttonSize))
	{
		V.z = resetValue.z;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &V.z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
}

void LImGui::DisplayVector4(FVector4 & V, const std::string & name, const FVector4 & resetValue, const FButtonColorPalette & xColorPalette, const FButtonColorPalette & yColorPalette, const FButtonColorPalette & zColorPalette, const FButtonColorPalette & wColorPalette)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = ImVec2(lineHeight + 3.f, lineHeight);

	ImGui::PushStyleColor(ImGuiCol_Button, xColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, xColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, xColorPalette.activeColor);

	if (ImGui::Button("X", buttonSize))
	{
		V.x = resetValue.x;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &V.x, 0.1f, 0.0f, 0.0f, "%.3f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, yColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, yColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, yColorPalette.activeColor);

	if (ImGui::Button("Y", buttonSize))
	{
		V.y = resetValue.y;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &V.y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, zColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, zColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, zColorPalette.activeColor);

	if (ImGui::Button("Z", buttonSize))
	{
		V.z = resetValue.z;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &V.z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, wColorPalette.defaultColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, wColorPalette.hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, wColorPalette.activeColor);

	if (ImGui::Button("W", buttonSize))
	{
		V.w = resetValue.w;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##W", &V.w, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);
	ImGui::PopID();
}
