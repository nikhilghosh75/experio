#define console

#include "GDebug.h"

#ifdef console
#include <iostream>
#include <windows.h>
using namespace std;
#endif

void GDebug::Log(string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << s << endl;
#endif

	FDebugInfo newInfo(EDebugType::Normal, s, FDateTime::NowHighRes());
	debugInfo.Append(newInfo);
}

void GDebug::LogWarning(string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << s << endl;
#endif

	FDebugInfo newInfo(EDebugType::Warning, s, FDateTime::NowHighRes());
	debugInfo.Append(newInfo);
}

void GDebug::LogError(string s)
{
#ifdef console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << s << endl;
#endif

	FDebugInfo newInfo(EDebugType::Error, s, FDateTime::NowHighRes());
	debugInfo.Append(newInfo);
}
