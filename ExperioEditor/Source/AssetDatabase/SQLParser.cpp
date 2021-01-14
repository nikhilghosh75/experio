#include "SQLParser.h"
#include "Runtime/Containers/LString.h"

static const std::vector<std::string> sqlKeywords = { "ALL", "AND", "ANY", "BETWEEN", 
	"CASE", "EXISTS", "FROM", "GROUP BY", "IN", "OR", "SELECT", "WHERE"};

SQLCommand SQLParser::ParseCommand(const std::string & str)
{
	SQLCommand command;
	
	command.commandType = GetCommandType(str);
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
