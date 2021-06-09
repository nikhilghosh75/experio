#include "NotificationSystem.h"
#include "../ProjectSettings/LanguageSettings.h"

std::vector<Notification*> NotificationSystem::notifications;

TextNotification* NotificationSystem::compileNotification;

extern FCompilationInfo GetCompilationInfo();

void TextNotification::Display()
{
	ImGui::Text(text.c_str());
}

void NotificationSystem::CalculateNotifications()
{
	FCompilationInfo compilationInfo = GetCompilationInfo();
	compileNotification->text = compilationInfo.isCompiling ? "Compiling" : "Compilation Done";
	compileNotification->visible = ShouldRenderCompileNotification(compilationInfo);
}

void NotificationSystem::RenderNotifications()
{
	for (size_t i = 0; i < notifications.size(); i++)
	{
		if (notifications[i]->visible)
		{
			ImVec4 windowBgCol = notifications[i]->color;
			ImGui::PushStyleColor(ImGuiCol_WindowBg, windowBgCol);
			SetNextWindowSize();

			ImGui::Begin(notifications[i]->name.c_str(), NULL, notifications[i]->flags);
			notifications[i]->Display();
			ImGui::End();

			ImGui::PopStyleColor();
		}
	}
}

void NotificationSystem::Initialize()
{
	compileNotification = new TextNotification();
	compileNotification->color = FColor(0.1f, 0.4f, 0.1f, 1.0f);
	compileNotification->flags = ImGuiWindowFlags_NoTitleBar;
	compileNotification->name = "Compilation";
	AddNotification(compileNotification);
}

void NotificationSystem::AddNotification(Notification* notification)
{
	notifications.push_back(notification);
}

/*

void NotificationSystem::RenderCompileNotification()
{
	FCompilationInfo compilationInfo = GetCompilationInfo();

	if (ShouldRenderCompileNotification(compilationInfo))
	{	
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
*/

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