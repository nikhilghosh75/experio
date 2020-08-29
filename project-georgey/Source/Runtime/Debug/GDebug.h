#pragma once
#include <string>
#include <vector>
#include "../Time/FDateTime.h"
using namespace std;

enum EDebugType
{
	Normal,
	Warning,
	Error
};

struct FDebugInfo
{
	EDebugType type;
	string message;
	FDateTime time;

	FDebugInfo(EDebugType newType, string newMessage, FDateTime newTime)
	{
		type = newType;
		message = newMessage;
		time = newTime;
	}
};

class GDebug
{
private:
	static std::vector<FDebugInfo> debugInfo;

public:
	static void Log(string s);
	static void LogWarning(string s);
	static void LogError(string s);
};