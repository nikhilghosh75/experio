#include "Console.h"

Console::Console()
{
	this->name = "Console";
	this->category = EEditorModuleCategory::Core;
}

void Console::Display()
{
	std::vector<FDebugInfo>& debugInfo = Debug::GetDebugInfo();

	if (ImGui::Button("Clear Console"))
	{
		startIndex = debugInfo.size();
	}

	ImGuiListClipper clipper;
	clipper.Begin(debugInfo.size());

	while (clipper.Step())
	{
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			ImGui::Text(debugInfo[i].message.c_str());
			/*
			if (debugInfo[i].messageType == EDebugMessageType::Normal)
			{
				switch (debugInfo[i].type)
				{
				case EDebugType::Normal:
					ImGui::Text(debugInfo[i].message.c_str()); break;
				case EDebugType::Warning:
					ImGui::TextColored(ImVec4(1, 1, 0, 1), debugInfo[i].message.c_str()); break;
				case EDebugType::Error:
					ImGui::TextColored(ImVec4(1, 0, 0, 1), debugInfo[i].message.c_str()); break;
				}
			}
			*/
		}
	}

	clipper.End();
}
