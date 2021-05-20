#pragma once
#include <vector>
#include <string>

/// <summary>
/// A class representing a datatable.
/// Intended to query easily
/// </summary>

enum class EDataColumnType
{
	INT,
	FLOAT,
	STRING,
	NONE
};

class DatatableRow;
class DatatableColumn;
class DatatableEntry;

class Datatable
{
	std::vector<std::vector<int32_t>> intColumns;
	std::vector<std::vector<float>> floatColumns;
	std::vector<std::vector<std::string>> stringColumns;

	std::vector<std::string> columnTitles;
	std::vector<EDataColumnType> columnTypes;

public:
	Datatable();
	Datatable(std::vector<std::vector<int32_t>> intColumns, std::vector<std::vector<float>> floatColumns,
		std::vector<std::vector<std::string>> stringColumns, std::vector<std::string> columnTitles, 
		std::vector<EDataColumnType> columnTypes);

	static const int32_t NotFoundInt;
	static const float NotFoundFloat;
	static const std::string NotFoundString;

	uint32_t RowCount() const;
	uint32_t ColumnCount() const;
	uint32_t Count() const;

	DatatableRow operator[](uint32_t rowIndex);
	
	DatatableRow GetRow(uint32_t rowIndex);
	DatatableColumn GetColumn(uint32_t columnIndex);

	DatatableEntry Get(uint32_t row, uint32_t column);

	std::string& GetString(uint32_t row, uint32_t column);
	float& GetFloat(uint32_t row, uint32_t column);
	int32_t& GetInt(uint32_t row, uint32_t column);

	void InsertColumn(std::string columnName, EDataColumnType columnType);

	void InsertFloatColumn(std::string& columnName, std::vector<float>& floatColumn);
	void InsertIntColumn(std::string& columnName, std::vector<int32_t>& intColumn);
	void InsertStringColumn(std::string& columnName, std::vector<std::string>& stringColumn);

	uint32_t GetSize() const;

	friend class DatatableRow;
	friend class DatatableColumn;
	friend class DatatableEntry;
};

class DatatableRow
{
	Datatable* table;
	uint32_t rowIndex;

public:
	DatatableRow();
	DatatableRow(Datatable* table, uint32_t rowIndex);

	DatatableEntry operator[](uint32_t columnIndex) const;
};

class DatatableColumn
{
	Datatable* table;
	uint32_t internalColumnIndex;
	uint32_t columnIndex;
	EDataColumnType columnType;

public:
	DatatableColumn();
	DatatableColumn(Datatable* table, uint32_t columnIndex);

	EDataColumnType ColumnType() const { return columnType; }

	const std::string& ColumnName() const;

	DatatableEntry operator[](uint32_t rowIndex) const;
};

class DatatableEntry
{
	Datatable* table;
	uint32_t rowIndex;
	uint32_t internalColumnIndex;
	EDataColumnType columnType;

public:
	DatatableEntry();
	DatatableEntry(Datatable* table, uint32_t rowIndex, uint32_t internalColumnIndex, EDataColumnType columnType);

	operator std::string&();
	operator float&();
	operator int32_t&();

	EDataColumnType ColumnType() const { return columnType; }
	bool IsString() const { return columnType == EDataColumnType::STRING; }
	bool IsFloat() const { return columnType == EDataColumnType::FLOAT; }
	bool IsInt() const { return columnType == EDataColumnType::INT; }
};
