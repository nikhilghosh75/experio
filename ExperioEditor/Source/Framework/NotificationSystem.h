#pragma once
#include <stdint.h>
#include <vector>
#include "imgui.h"
#include "Compilation/CompilationInfo.h"
#include "Runtime/Math/FColor.h"

struct Notification
{
	std::string name;
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar;
	FColor color;
	bool visible = true;
	
	virtual void Display() {}
};

struct TextNotification : public Notification
{
	std::string text;

	virtual void Display() override;
};

class NotificationSystem
{
public:
	static void CalculateNotifications();

	static void RenderNotifications();

	static void Initialize();

	static void AddNotification(Notification* notification);
	
private:
	static std::vector<Notification*> notifications;

	static TextNotification* compileNotification;

	static void SetNextWindowSize();

	static bool ShouldRenderCompileNotification(const FCompilationInfo info);
};