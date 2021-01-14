#pragma once

#include <string>
#include <vector>

/*
SELECT name FROM meshes WHERE (serializedSize > 1000000 AND UsedIn(TestScene.pbscene))
*/

enum class ESQLCommandType
{
	None,
	Exists,
	Select
};

enum class ESQLConditionType
{
	GreaterThan,
	GreaterThanOrEqualTo,
	Equal,
	LessThanOrEqualTo,
	LessThan
};

class SQLCondition
{
public:
	ESQLConditionType conditionType;
	std::string param[2];
};

class SQLCommand
{
public:
	std::vector<std::string> columnsToSelect;
	std::vector<std::string> tables;
	std::vector<SQLCondition> conditions;
	ESQLCommandType commandType;
};