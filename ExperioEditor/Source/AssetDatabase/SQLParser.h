#pragma once
#include "SQLCommand.h"
#include "Runtime/Math/FVector2Int.h"

class SQLParser
{
public:
	static SQLCommand ParseCommand(const std::string& str);

private:
	static ESQLCommandType GetCommandType(const std::string& str);

	static size_t GetNextKeywordPosition(const std::string& str, size_t startPosition = 0);

	static void ParseSelectCommand(const std::string& str, SQLCommand& command);

	static void ParseExistsCommand(const std::string& str, SQLCommand& command);

	static FVector2Int GetConditionBounds(const std::string& str, size_t startPosition = 0);

	static void ParseConditions(const std::string& str, SQLCommand& command, size_t start, size_t end);

	static SQLCondition ParseCondition(const std::string& str);
};