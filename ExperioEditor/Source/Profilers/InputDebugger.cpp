#include "InputDebugger.h"
#include "Runtime/Input/Input.h"
#include "ThirdParty/Magic Enum/magic_enum.hpp"

InputDebugger::InputDebugger()
{
	this->name = "Input Debugger";
	this->category = EEditorModuleCategory::Profiling;
}

void InputDebugger::Display()
{
	if (ImGui::TreeNode("Mouse"))
	{
		MouseDebugger();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Keyboard"))
	{
		KeyboardDebugger();
		ImGui::TreePop();
	}
}

void InputDebugger::MouseDebugger()
{
	FVector2 mousePosition = Input::GetMousePosition();
	ImGui::Text("Mouse Position:"); ImGui::SameLine(); ImGui::Text(((std::string)mousePosition).c_str());

	FVector2 mouseDelta = Input::GetMouseDelta();
	ImGui::Text("Mouse Delta:"); ImGui::SameLine(); ImGui::Text(((std::string)mouseDelta).c_str());

	ImGui::Text("Mouse Scroll Vertical:");
	ImGui::SameLine();
	ImGui::Text(std::to_string(Input::GetMouseScrollDelta()).c_str());

	ImGui::Text("Mouse Scroll Horizontal:");
	ImGui::SameLine();
	ImGui::Text(std::to_string(Input::GetMouseHScrollDelta()).c_str());

	ImGui::Text("Left Mouse Button:");
	ImGui::SameLine();
	ImGui::Text(Input::GetMouseButton(EMouseButton::Left) ? "true" : "false");

	ImGui::Text("Middle Mouse Button:");
	ImGui::SameLine();
	ImGui::Text(Input::GetMouseButton(EMouseButton::Middle) ? "true" : "false");

	ImGui::Text("Right Mouse Button:");
	ImGui::SameLine();
	ImGui::Text(Input::GetMouseButton(EMouseButton::Right) ? "true" : "false");
}

void InputDebugger::KeyboardDebugger()
{
	if (!Input::AnyKey())
	{
		ImGui::Text("No keys are pressed");
		return;
	}

	ImGui::Text("Keys pressed:");

	for (int i = 0; i < PB_NUM_KEY_CODES; i++)
	{
		if (Input::GetKey((EKeyCode)i))
		{
			ImGui::Text(magic_enum::enum_name<EKeyCode>((EKeyCode)i).data());
		}
	}
}
