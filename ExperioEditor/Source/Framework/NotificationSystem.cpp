#include "NotificationSystem.h"
#include "imgui.h"
#include "../ProjectSettings/LanguageSettings.h"

uint8_t NotificationSystem::numNotifications = 0;

extern FCompilationInfo GetCompilationInfo();

void NotificationSystem::RenderNotifications()
{
	numNotifications = 0;

	RenderCompileNotification();
}

void NotificationSystem::RenderCompileNotification()
{
	FCompilationInfo compilationInfo = GetCompilationInfo();

	if (ShouldRenderCompileNotification(compilationInfo))
	{
		numNotifications++;
		
		ImVec4 windowBgCol = ImVec4(0.1f, 0.4f, 0.1f, 1.0f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, windowBgCol);
		SetNextWindowSize();
		ImGui::Begin("Compiling", NULL, ImGuiWindowFlags_NoTitleBar);
		if (compilationInfo.isCompiling)
		{
			ImGui::Text("Compiling");
		}
		else
		{
			ImGui::Text("Compile Done");
		}
		ImGui::End();
		ImGui::PopStyleColor();
	}
}

bool NotificationSystem::ShouldRenderCompileNotification(const FCompilationInfo info)
{
	float showAfterCompileTime = LanguageSettings::languageSettings->showAfterCompileTime;

	return info.isCompiling || (info.timeSinceLastCompile > 0 && info.timeSinceLastCompile < showAfterCompileTime);
}

void NotificationSystem::SetNextWindowSize()
{
	// Modify Later
	ImVec2 imguiWindowSize = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos(ImVec2(imguiWindowSize.x - 300, imguiWindowSize.y - 50), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(280, 0), ImGuiCond_Always);
}
