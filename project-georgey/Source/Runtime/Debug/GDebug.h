#pragma once
#include <string>
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
};

class GDebug
{
public:
	static void Log(string s);
	static void LogWarning(string s);
	static void LogError(string s);
};