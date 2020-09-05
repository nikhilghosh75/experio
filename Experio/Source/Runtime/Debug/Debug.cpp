#define console

#include "Debug.h"

#ifdef console
#include <iostream>
#include <windows.h>
#endif

std::vector<FDebugInfo> Debug::debugInfo;

void Debug::Log(std::string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << s << std::endl;
#endif

	FDebugInfo newInfo(EDebugType::Normal, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}

void Debug::LogWarning(std::string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << s << std::endl;
#endif

	FDebugInfo newInfo(EDebugType::Warning, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}

void Debug::LogError(std::string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	std::cout << s << std::endl;
#endif

	FDebugInfo newInfo(EDebugType::Error, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}
