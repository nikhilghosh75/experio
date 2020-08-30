#define console

#include "Debug.h"

#ifdef console
#include <iostream>
#include <windows.h>
#endif

std::vector<FDebugInfo> Debug::debugInfo;

void Debug::Log(string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << s << endl;
#endif

	FDebugInfo newInfo(EDebugType::Normal, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}

void Debug::LogWarning(string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << s << endl;
#endif

	FDebugInfo newInfo(EDebugType::Warning, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}

void Debug::LogError(string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << s << endl;
#endif

	FDebugInfo newInfo(EDebugType::Error, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}
