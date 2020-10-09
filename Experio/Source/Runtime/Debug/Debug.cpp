#define PB_LOG_CONSOLE

#include "Debug.h"
#include "../../ThirdParty/Nameof/nameof.hpp"

#ifdef PB_LOG_CONSOLE
#include <iostream>
#include <windows.h>
#endif
#ifdef PB_LOG_FILE
#include <sstream>
#include <fstream>
#endif

std::vector<FDebugInfo> Debug::debugInfo;

DebugStream Debug::log(EDebugType::Normal);
DebugStream Debug::warningLog(EDebugType::Warning);
DebugStream Debug::errorLog(EDebugType::Error);

// Constants
DebugConstant Debug::endl(5807);

void Debug::Log(std::string s)
{
#ifdef PB_LOG_CONSOLE
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << s << std::endl;
#endif

	FDebugInfo newInfo(EDebugType::Normal, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}

void Debug::LogWarning(std::string s)
{
#ifdef PB_LOG_CONSOLE
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << s << std::endl;
#endif

	FDebugInfo newInfo(EDebugType::Warning, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}

void Debug::LogError(std::string s)
{
#ifdef PB_LOG_CONSOLE
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	std::cout << s << std::endl;
#endif

	FDebugInfo newInfo(EDebugType::Error, s, FDateTime::NowHighRes());
	debugInfo.push_back(newInfo);
}

void Debug::FlushToFile()
{
#ifdef PB_LOG_FILE
	std::ofstream debugFile("pboutput.txt");

	for (int i = 0; i < debugInfo.size(); i++)
	{
		switch (debugInfo[i].type)
		{
		case EDebugType::Warning:
			debugFile << "%WARNING:%"; break;
		case EDebugType::Error:
			debugFile << "%ERROR%"; break;
		}

		debugFile << debugInfo[i].message << " %TIME% " << FDateTime::DateToString(debugInfo[i].time) << std::endl;
	}

	debugFile.close();
#endif
}

void DebugStream::SetType(EDebugType type)
{
#ifdef PB_LOG_CONSOLE
	switch (type)
	{
	case EDebugType::Normal:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
	case EDebugType::Warning:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); break;
	case EDebugType::Error:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); break;
	}
#endif

}

void DebugStream::FlushMessages()
{
	std::stringstream ss;
	for (int i = 0; i < this->currentDebuggedMessage; i++)
	{
		ss << this->debuggedMessages[i];
	}
	Debug::debugInfo.emplace_back(this->type, ss.str(), FDateTime::NowHighRes());
	this->currentDebuggedMessage = 0;
}

DebugStream::DebugStream(EDebugType type)
{
	this->type = type;
}

DebugStream& DebugStream::operator<<(std::string str)
{
	SetType(this->type);
#ifdef PB_LOG_CONSOLE
	std::cout << str;
#endif
#ifdef PB_LOG_FILE
	this->debuggedMessages[this->currentDebuggedMessage] = str;
	this->currentDebuggedMessage++;
#endif
	return *this;
}

DebugStream& DebugStream::operator<<(DebugConstant constant)
{
	switch (constant.constant)
	{
	case 5807: // Endl
#ifdef PB_LOG_CONSOLE
		std::cout << std::endl;
#endif
#ifdef PB_LOG_FILE
		FlushMessages();
#endif

		break;
	}
	return *this;
}

DebugStream& operator<<(DebugStream& stream, int i)
{
	stream << std::to_string(i);
	return stream;
}

DebugStream& operator<<(DebugStream & stream, float f)
{
	stream << std::to_string(f);
	return stream;
}

DebugStream& operator<<(DebugStream & stream, unsigned int i)
{
	stream << std::to_string(i); 
	return stream;
}
