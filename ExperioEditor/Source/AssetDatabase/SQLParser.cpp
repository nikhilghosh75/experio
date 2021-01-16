#include "SQLParser.h"
#include "Runtime/Containers/LString.h"

static const std::vector<std::string> sqlKeywords = { "ALL", "AND", "ANY", "BETWEEN", 
	"CASE", "EXISTS", "FROM", "GROUP BY", "IN", "OR", "SELECT", "WHERE"};

SQLCommand SQLParser::ParseCommand(const std::string & str)
{
	SQLCommand command;
	
	command.commandType = GetCommandType(str);
	switch (command.commandType)
	{
	case ESQLCommandType::Select:
		ParseSelectCommand(str, command); break;
	case ESQLCommandType::Exists:
		ParseExistsCommand(str, command); break;
	}

	return command;
}

ESQLCommandType SQLParser::GetCommandType(const std::string & str)
{
	if (str.find("SELECT") == 0) return ESQLCommandType::Select;
	if (str.find("EXISTS") == 0) return ESQLCommandType::Exists;
	return ESQLCommandType::None;
}

size_t SQLParser::GetNextKeywordPosition(const std::string & str, size_t startPosition)
{
	size_t minPosition = str.find(sqlKeywords[0], startPosition);
	for (size_t i = 1; i < sqlKeywords.size(); i++)
	{
		size_t tempPosition = str.find(sqlKeywords[i], startPosition);
		if (tempPosition < minPosition && tempPosition >= startPosition)
		{
			minPosition = tempPosition;
		}
	}
	return minPosition;
}

void SQLParser::ParseSelectCommand(const std::string & str, SQLCommand& command)
{
	size_t nextKeywordPosition = GetNextKeywordPosition(str, 7);
	if (nextKeywordPosition != 7 && str[7] == '*')
	{
		command.columnsToSelect = LString::SeperateStringByChar(str.substr(7, nextKeywordPosition - 7), ',', true);
		for (size_t i = 0; i < command.columnsToSelect.size(); i++)
		{
			command.columnsToSelect[i] = LString::Trim(command.columnsToSelect[i]);
		}
	}

	nextKeywordPosition = GetNextKeywordPosition(str, nextKeywordPosition + 2);
	if (LString::CompareSubstr(str, "FROM", nextKeywordPosition))
	{
		if (str[nextKeywordPosition + 5] != '*')
		{
			size_t startOfTables = nextKeywordPosition + 5;
			nextKeywordPosition = GetNextKeywordPosition(str, nextKeywordPosition + 5);
			command.tables = LString::SeperateStringByChar(str.substr(startOfTables, nextKeywordPosition - startOfTables), ',', true);
		}
	}
	// Add other command types here
}

void SQLParser::ParseExistsCommand(const std::string & str, SQLCommand& command)
{
}
