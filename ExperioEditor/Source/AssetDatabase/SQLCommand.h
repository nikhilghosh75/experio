#pragma once

#include <string>
#include <vector>

/*
SELECT name FROM meshes WHERE (serializedSize > 1000000 AND UsedIn(TestScene.pbscene))
EXISTS ANY FROM meshes WHERE (serializedSize > 1000000 OR UsedIn(TestScene.pbscene))
*/

enum class ESQLCommandType
{
	None,
	Exists,
	Select
};

enum class EBoolOperatorType
{
	None,
	And,
	Or,
	Xor
};

enum class ESQLConditionType
{
	None,
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
	EBoolOperatorType boolOperator;
	ESQLCommandType commandType;
};