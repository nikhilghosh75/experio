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

struct DebugConstant
{
	unsigned short constant;

	DebugConstant(unsigned short constant) { this->constant = constant; }
};

class DebugStream
{
	EDebugType type;

	std::string debuggedMessages[32];
	int currentDebuggedMessage = 0;

	void SetType(EDebugType type);

	void FlushMessages();
public:
	DebugStream(EDebugType type);

	DebugStream& operator<<(std::string str);
	DebugStream& operator<<(DebugConstant constant);
};

DebugStream& operator<<(DebugStream& stream, int i);
DebugStream& operator<<(DebugStream& stream, float f);
DebugStream& operator<<(DebugStream& stream, unsigned int i);
DebugStream& operator<<(DebugStream& stream, uint8_t i);
DebugStream& operator<<(DebugStream& stream, uint16_t i);
DebugStream& operator<<(DebugStream& stream, uint64_t i);

class Debug
{
	friend class DebugStream;
private:
	static std::vector<FDebugInfo> debugInfo;

public:
	// Streams
	static DebugStream log;
	static DebugStream warningLog;
	static DebugStream errorLog;

	// Constants
	static DebugConstant endl;

	static void Log(std::string s);
	static void LogWarning(std::string s);
	static void LogError(std::string s);

	static void FlushToFile();
};
