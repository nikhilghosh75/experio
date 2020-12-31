#pragma once
#include <stdint.h>
#include "Compilation/CompilationInfo.h"

class NotificationSystem
{
public:
	static void RenderNotifications();
	
private:
	static uint8_t numNotifications;

	static void RenderCompileNotification();

	static bool ShouldRenderCompileNotification(const FCompilationInfo info);

	static void SetNextWindowSize();
};