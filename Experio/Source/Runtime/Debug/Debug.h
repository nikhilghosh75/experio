#pragma once
#include <string>
#include <vector>
#include "../Time/FDateTime.h"

enum EDebugType
{
	Normal,
	Warning,
	Error
};

struct FDebugInfo
{
	EDebugType type;
	std::string message;
	FDateTime time;

	FDebugInfo(EDebugType newType, std::string newMessage, FDateTime newTime)
	{
		type = newType;
		message = newMessage;
		time = newTime;
	}
};

class Debug
{
private:
	static std::vector<FDebugInfo> debugInfo;

public:
	static void Log(std::string s);
	static void LogWarning(std::string s);
	static void LogError(std::string s);
};