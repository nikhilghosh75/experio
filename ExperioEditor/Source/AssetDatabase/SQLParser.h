#pragma once
#include "SQLCommand.h"

class SQLParser
{
public:
	static SQLCommand ParseCommand(const std::string& str);

private:
	static ESQLCommandType GetCommandType(const std::string& str);

	static size_t GetNextKeywordPosition(const std::string& str, size_t startPosition = 0);
};