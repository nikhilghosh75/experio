#pragma once

#include "RuntimeCompiler/ICompilerLogger.h"
#include "Framework/Compilation/CompilationParser.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <Windows.h>

#pragma warning(disable : 4996 4800)

// StdioLogSystem for compiler
const size_t LOGSYSTEM_MAX_BUFFER = 4096;

class DemoProjectLogger : public ICompilerLogger
{
	char m_buff[LOGSYSTEM_MAX_BUFFER];

	void LogInternal(const char * format, va_list args)
	{
		vsnprintf(m_buff, LOGSYSTEM_MAX_BUFFER - 1, format, args);
		// Make sure there's a limit to the amount of rubbish we can output
		m_buff[LOGSYSTEM_MAX_BUFFER - 1] = '\0';

		std::cout << m_buff;
#ifdef _WIN32
		OutputDebugStringA(m_buff);
#endif
		CompilationParser::Read(m_buff);
	}

public:
	virtual void LogError(const char * format, ...) override
	{
		va_list args;
		va_start(args, format);
		LogInternal(format, args);
	}

	virtual void LogWarning(const char * format, ...) override
	{
		va_list args;
		va_start(args, format);
		LogInternal(format, args);
	}
	virtual void LogInfo(const char * format, ...)
	{
		va_list args;
		va_start(args, format);
		LogInternal(format, args);
	}
	virtual ~DemoProjectLogger() {}
};