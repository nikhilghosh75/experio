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

	for (int i = startIndex; i < debugInfo.size(); i++)
	{
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
			ImGui::Text(debugInfo[i].message.c_str());
		}
	}
}
