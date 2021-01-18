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
	if (nextKeywordPosition != 7 && str[7] != '*')
	{
		command.columnsToSelect = LString::SeperateStringByChar(str.substr(7, nextKeywordPosition - 7), ',', true);
		for (size_t i = 0; i < command.columnsToSelect.size(); i++)
		{
			command.columnsToSelect[i] = LString::Trim(command.columnsToSelect[i]);
		}
	}

	if (LString::CompareSubstr(str, "FROM", nextKeywordPosition))
	{
		if (str[nextKeywordPosition + 5] != '*')
		{
			size_t startOfTables = nextKeywordPosition + 5;
			nextKeywordPosition = GetNextKeywordPosition(str, nextKeywordPosition + 5);
			command.tables = LString::SeperateStringByChar(str.substr(startOfTables, nextKeywordPosition - startOfTables), ',', true);
		}
	}

	// nextKeywordPosition = GetNextKeywordPosition(str, nextKeywordPosition + 2);
	if (LString::CompareSubstr(str, "WHERE", nextKeywordPosition))
	{
		FVector2Int conditionBounds = GetConditionBounds(str, nextKeywordPosition - 1);
		ParseConditions(str, command, (size_t)conditionBounds.x, (size_t)conditionBounds.y);
	}
}

void SQLParser::ParseExistsCommand(const std::string & str, SQLCommand& command)
{
}

FVector2Int SQLParser::GetConditionBounds(const std::string & str, size_t startPosition)
{
	int start = str.find('(', startPosition);
	int end = startPosition;
	int levelIn = 0;
	for (size_t i = startPosition; i < str.size(); i++)
	{
		if (str[i] == '(')
		{
			levelIn++;
		}
		else if (str[i] == ')')
		{
			end = i;
			levelIn--;
			if (levelIn <= 0)
				break;
		}
	}
	return FVector2Int(start, end);
}

void SQLParser::ParseConditions(const std::string& str, SQLCommand& command, size_t start, size_t end)
{
	size_t lastConditionPosition = start + 1;
	for (size_t i = start; i < end; i++)
	{
		if (LString::CompareSubstr(str, "AND", i))
		{
			command.boolOperator = EBoolOperatorType::And;
			command.conditions.push_back(ParseCondition(str.substr(lastConditionPosition, i - lastConditionPosition)));
			i += 3;
			lastConditionPosition = i;
		}
		else if (LString::CompareSubstr(str, "OR", i))
		{
			command.boolOperator = EBoolOperatorType::Or;
			command.conditions.push_back(ParseCondition(str.substr(lastConditionPosition, i - lastConditionPosition)));
			i += 2;
			lastConditionPosition = i;
		}
	}
	command.conditions.push_back(ParseCondition(str.substr(lastConditionPosition, end - lastConditionPosition)));
}

SQLCondition SQLParser::ParseCondition(const std::string & str)
{
	SQLCondition condition;
	condition.conditionType = ESQLConditionType::None;
	size_t foundPosition;
	
	// Less Than
	foundPosition = str.find("<");
	if (foundPosition != std::string::npos)
	{
		condition.conditionType = ESQLConditionType::LessThan;
		condition.param[0] = str.substr(0, foundPosition - 1);
		condition.param[1] = str.substr(foundPosition + 1);
	}

	// Greater Than
	foundPosition = str.find(">");
	if (foundPosition != std::string::npos)
	{
		condition.conditionType = ESQLConditionType::GreaterThan;
		condition.param[0] = str.substr(0, foundPosition - 1);
		condition.param[1] = str.substr(foundPosition + 1);
	}

	// Less Than Or Equal To
	foundPosition = str.find("<=");
	if (foundPosition != std::string::npos)
	{
		condition.conditionType = ESQLConditionType::LessThanOrEqualTo;
		condition.param[0] = str.substr(0, foundPosition - 1);
		condition.param[1] = str.substr(foundPosition + 2);
	}

	// Greater Than Or Equal To
	foundPosition = str.find(">=");
	if (foundPosition != std::string::npos)
	{
		condition.conditionType = ESQLConditionType::GreaterThanOrEqualTo;
		condition.param[0] = str.substr(0, foundPosition - 1);
		condition.param[1] = str.substr(foundPosition + 2);
	}

	return condition;
}
