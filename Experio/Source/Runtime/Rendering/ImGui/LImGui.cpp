#include "LImGui.h"
#include "../../Debug/Debug.h"
#include "../../Containers/Algorithm.h"
#include "../../Containers/LString.h"
#include "../../Files/LFileOperations.h"
#include "../Managers/FontManager.h"
#include "../Managers/MeshManager.h"
#include "../Managers/TextureManager.h"
#include "imgui_internal.h"

struct InputTextCallback_UserData
{
	std::string* Str;
	ImGuiInputTextCallback  ChainCallback;
	void* ChainCallbackUserData;
};

using namespace Experio;

uint64_t LImGui::DisplayBitmask(std::string name, const std::vector<std::string>& names, bool* selected)
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

void LImGui::DisplayBox(FBox & box, std::string name)
{
	if (ImGui::TreeNode(name.c_str()))
	{
		LImGui::DisplayVector3(box.min, "Min");
		LImGui::DisplayVector3(box.max, "Max");
		ImGui::TreePop();
	}
}

void LImGui::DisplayColorSmall(ImU32 color32, std::string name)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	float sz = ImGui::GetTextLineHeight();
	ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), color32);
	ImGui::Dummy(ImVec2(sz, sz));
	ImGui::SameLine();
	ImGui::Text(name.c_str());
}

void LImGui::DisplayCurve(const char* label, Bezier& bezier, ImGuiBezierCurveState& bezierState)
{
	ImGui::BeginChildFrame(ImGui::GetID(label), ImVec2(0, 50), ImGuiWindowFlags_NoMove);

	ImGui::EndChildFrame();
}

void LImGui::DisplayFileAsset(FileRef & ref, std::string name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	std::string fileName = LFileOperations::StripFilename(ref.filepath);
	ImGui::Text(fileName.c_str());

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_FILE"))
		{
			ref.filepath = (char*)payload->Data;
		}
		else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_FONT"))
		{
			ref.filepath = (char*)payload->Data;
		}
		else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_MESH"))
		{
			ref.filepath = (char*)payload->Data;
		}
		else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_IMAGE"))
		{
			ref.filepath = (char*)payload->Data;
		}
		else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_TEXT"))
		{
			ref.filepath = (char*)payload->Data;
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

void LImGui::DisplayFontAsset(FontRef & ref, std::string name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	if (ref.IsNull())
	{
		ImGui::Text("Null");
	}
	else
	{
	std::string fontFileName = FontManager::GetNameOfFont(ref);
	std::string fontName = LFileOperations::StripFilename(fontFileName);
	ImGui::Text(fontName.c_str());
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_FONT"))
		{
			char* fontName = (char*)payload->Data;
			LFileOperations::CorrectFilepath(fontName);
			ref = FontManager::LoadFont(fontName);
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

void LImGui::DisplayLayer(uint8_t& layer, const THashtable<uint16_t, std::string>& layerTable)
{
	uint16_t layer16 = layer;
	std::string layerName;
	bool found = layerTable.SafeGet(layer16, layerName);

	if (!found)
		layerName = "Multiple";

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

void LImGui::DisplayMaterial(Material * material, const std::string& name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	if (material == nullptr)
	{
		ImGui::Text("Null");
	}
	else
	{
		std::string& materialName = Project::materialManager->materialNames[material->GetID()];
		ImGui::Text(materialName.c_str());
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_MATERIAL"))
		{
			Material* tempMaterial = Project::materialManager->LoadMaterialFromFile((char*)payload->Data);
			if (tempMaterial != nullptr)
			{
				material = tempMaterial;
			}
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

void LImGui::DisplayMeshAsset(MeshRef & ref, const std::string& name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	if (ref.IsNull())
	{
		ImGui::Text("Null");
	}
	else
	{
		std::string meshFileName = MeshManager::GetNameOfMesh(ref);
		std::string meshName = LFileOperations::StripFilename(meshFileName);
		ImGui::Text(meshName.c_str());
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_MESH"))
		{
			char* meshName = (char*)payload->Data;
			LFileOperations::CorrectFilepath(meshName);
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

void LImGui::DisplayQuaternion(FQuaternion& quat, const std::string& name)
{
	FVector4 rotationV = FVector4(quat.w, quat.x, quat.y, quat.z);
	DisplayVector4(rotationV, "Rotation", FVector4(1, 0, 0, 0));
	quat = FQuaternion(rotationV.x, rotationV.y, rotationV.z, rotationV.w);
}

void LImGui::DisplayRect(FRect& rect, const std::string & name)
{
	if (ImGui::TreeNode(name.c_str()))
	{
		LImGui::DisplayVector2(rect.min, "Min");
		LImGui::DisplayVector2(rect.max, "Max");
		ImGui::TreePop();
	}
}

bool LImGui::DisplayString(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
	if (str->capacity() == 0)
		str->reserve(16);

	char* buffer = str->data();

	InputTextCallback_UserData cb_user_data;
	cb_user_data.Str = str;
	cb_user_data.ChainCallback = callback;
	cb_user_data.ChainCallbackUserData = user_data;
	bool changed = ImGui::InputText(label, buffer, str->capacity() + 1, flags, callback, &cb_user_data);
	*str = buffer;

	return changed;
}

void LImGui::DisplayTag(uint16_t& tag, const THashtable<uint16_t, std::string>& tagTable)
{
	std::string tagName;
	bool found = tagTable.SafeGet(tag, tagName);

	if (!found)
		tagName = "Multiple";
	
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

void LImGui::DisplayTextAsset(TextRef& ref, const std::string& name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	std::string fileName = LFileOperations::StripFilename(ref.filepath);
	ImGui::Text(fileName.c_str());

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_TEXT"))
		{
			ref.filepath = (char*)payload->Data;
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

void LImGui::DisplayTexture(TextureRef & ref, const std::string & name, unsigned int width, unsigned int height)
{
	ImGui::Text(name.c_str());
	ImGui::SameLine();
	ImGui::Image((void*)ref->GetRendererID(), ImVec2(width, height));
}

void LImGui::DisplayTextureAsset(TextureRef & ref, std::string name)
{
	ImGui::PushID(name.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.f);
	ImGui::Text(name.c_str());
	ImGui::NextColumn();

	if (ref.IsNull())
	{
		ImGui::Text("Null");
	}
	else
	{
	std::string meshFileName = TextureManager::GetNameOfTexture(ref);
	std::string meshName = LFileOperations::StripFilename(meshFileName);
	ImGui::Text(meshName.c_str());
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EXPERIO_IMAGE"))
		{
			char* imageName = (char*)payload->Data;
			LFileOperations::CorrectFilepath(imageName);
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

	if (ImGui::IsItemClicked())
	{
		selectedItem = tree->GetRoot()->object;
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

bool LImGui::FilterCombo(const char* label, char* buffer, int bufferlen, const char** hints, int num_hints, ImGuiFilterComboState& s, ImGuiFilterComboFlags flags)
{
	s.selectionChanged = false;

	ImGuiComboFlags comboFlags = 0;
	if (flags & ImGuiFilterComboFlags_HeightSmall)
		comboFlags = ImGuiComboFlags_HeightSmall;
	else if (flags & ImGuiFilterComboFlags_HeightRegular)
		comboFlags = ImGuiComboFlags_HeightRegular;

	if (ImGui::BeginCombo(label, buffer, comboFlags))
	{
		bool showAll = strlen(buffer) == 0;

		bool textChanged = ImGui::InputText("##Selection", buffer, bufferlen);
		
		for (int i = 0; i < num_hints; i++)
		{
			bool currentlySelected = i == s.activeIdx;
			bool showThisHint = showAll || LString::FuzzyMatch(buffer, hints[i]);
			if (showThisHint)
			{
				if (ImGui::Selectable(hints[i], &currentlySelected))
				{
					s.activeIdx = i;
					s.selectionChanged = true;
					strcpy(buffer, hints[i]);
				}
			}
		}
		
		ImGui::EndCombo();
	}
	else
	{
		return false;
	}

	return s.selectionChanged;
}
