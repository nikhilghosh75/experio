#include "Datatable.h"

const int32_t Datatable::NotFoundInt = std::numeric_limits<int32_t>::max();
const float Datatable::NotFoundFloat = std::numeric_limits<float>::max();
const std::string Datatable::NotFoundString = "ZZZZZZZZZZZZZZZZ";

Datatable::Datatable()
{
}

Datatable::Datatable(std::vector<std::vector<int32_t>> intColumns, std::vector<std::vector<float>> floatColumns, std::vector<std::vector<std::string>> stringColumns, std::vector<std::string> columnTitles, std::vector<EDataColumnType> columnTypes)
{
	this->intColumns = intColumns;
	this->floatColumns = floatColumns;
	this->stringColumns = stringColumns;
	this->columnTitles = columnTitles;
	this->columnTypes = columnTypes;
}

uint32_t Datatable::RowCount() const
{
	if (columnTypes.size() == 0)
	{
		return 0;
	}

	if (floatColumns.size() > 0) return floatColumns[0].size();
	if (intColumns.size() > 0) return intColumns[0].size();

	return stringColumns[0].size();
}

uint32_t Datatable::ColumnCount() const
{
	return columnTypes.size();
}

uint32_t Datatable::Count() const
{
	return RowCount() * ColumnCount();
}

DatatableRow Datatable::operator[](uint32_t rowIndex)
{
	return DatatableRow(this, rowIndex);
}

DatatableEntry Datatable::Get(uint32_t row, uint32_t column)
{
	EDataColumnType columnType = this->columnTypes[column];
	uint32_t columnIndex = 0;
	for (uint32_t i = 0; i < column; i++)
	{
		if (this->columnTypes[i] == columnType) columnIndex++;
	}
	return DatatableEntry(this, row, columnIndex, columnType);
}

std::string & Datatable::GetString(uint32_t row, uint32_t column)
{
	uint32_t columnIndex = 0;
	for (uint32_t i = 0; i < column; i++)
	{
		if (this->columnTypes[i] == EDataColumnType::STRING) columnIndex++;
	}
	return stringColumns[columnIndex][row];
}

float & Datatable::GetFloat(uint32_t row, uint32_t column)
{
	uint32_t columnIndex = 0;
	for (uint32_t i = 0; i < column; i++)
	{
		if (this->columnTypes[i] == EDataColumnType::FLOAT) columnIndex++;
	}
	return floatColumns[columnIndex][row];
}

int32_t & Datatable::GetInt(uint32_t row, uint32_t column)
{
	uint32_t columnIndex = 0;
	for (uint32_t i = 0; i < column; i++)
	{
		if (this->columnTypes[i] == EDataColumnType::INT) columnIndex++;
	}
	return intColumns[columnIndex][row];
}

void Datatable::InsertColumn(std::string columnName, EDataColumnType columnType)
{
	this->columnTitles.push_back(columnName);
	this->columnTypes.push_back(columnType);

	switch (columnType)
	{
	case EDataColumnType::FLOAT:
		floatColumns.push_back(std::vector<float>()); break;
	case EDataColumnType::INT:
		intColumns.push_back(std::vector<int32_t>()); break;
	case EDataColumnType::STRING:
		stringColumns.push_back(std::vector<std::string>()); break;
	}
}

void Datatable::InsertFloatColumn(std::string & columnName, std::vector<float>& floatColumn)
{
	this->columnTitles.push_back(columnName);
	this->columnTypes.push_back(EDataColumnType::FLOAT);
	this->floatColumns.push_back(floatColumn);
}

void Datatable::InsertIntColumn(std::string & columnName, std::vector<int32_t>& intColumn)
{
	this->columnTitles.push_back(columnName);
	this->columnTypes.push_back(EDataColumnType::INT);
	this->intColumns.push_back(intColumn);
}

void Datatable::InsertStringColumn(std::string & columnName, std::vector<std::string>& stringColumn)
{
	this->columnTitles.push_back(columnName);
	this->columnTypes.push_back(EDataColumnType::STRING);
	this->stringColumns.push_back(stringColumn);
}

uint32_t Datatable::GetSize() const
{
	uint32_t floatSize = floatColumns.size() * sizeof(float) * RowCount();
	uint32_t intSize = intColumns.size() * sizeof(int) * RowCount();

	uint32_t stringSize = 0;
	for (size_t i = 0; i < stringColumns.size(); i++)
	{
		for (size_t j = 0; j < stringColumns[i].size(); i++)
		{
			stringSize += stringColumns[i][j].capacity();
		}
	}

	return floatSize + intSize + stringSize;
}

DatatableRow::DatatableRow()
{
	this->table = nullptr;
	this->rowIndex = 0;
}

DatatableRow::DatatableRow(Datatable * table, uint32_t rowIndex)
{
	this->table = table;
	this->rowIndex = rowIndex;
}

DatatableEntry DatatableRow::operator[](uint32_t columnIndex) const
{
	EDataColumnType columnType = table->columnTypes[columnIndex];

	uint32_t internalColumnIndex = 0;
	for (int i = 0; i < columnIndex; i++)
	{
		if (table->columnTypes[i] == columnType) internalColumnIndex++;
	}
	return DatatableEntry(table, rowIndex, internalColumnIndex, columnType);
}

DatatableColumn::DatatableColumn()
{
	this->table = nullptr;
	this->columnIndex = 0;
	this->columnType = EDataColumnType::NONE;
}

DatatableColumn::DatatableColumn(Datatable * table, uint32_t columnIndex)
{
	this->table = table;
	this->columnType = table->columnTypes[columnIndex];
	this->columnIndex = 0;

	for (uint32_t i = 0; i < table->columnTypes.size(); i++)
	{
		if (table->columnTypes[i] == columnType) this->columnIndex++;
	}
}

DatatableEntry DatatableColumn::operator[](uint32_t rowIndex) const
{
	return DatatableEntry(this->table, rowIndex, this->columnIndex, this->columnType);
}

DatatableEntry::DatatableEntry()
{
	this->table = nullptr;
	this->rowIndex = 0;
	this->internalColumnIndex = 0;
	this->columnType = EDataColumnType::NONE;
}

DatatableEntry::DatatableEntry(Datatable * table, uint32_t rowIndex, uint32_t internalColumnIndex, EDataColumnType columnType)
{
	this->table = table;
	this->rowIndex = rowIndex;
	this->internalColumnIndex = internalColumnIndex;
	this->columnType = columnType;
}

DatatableEntry::operator std::string&()
{
	return table->stringColumns[internalColumnIndex][rowIndex];
}

DatatableEntry::operator float&()
{
	return table->floatColumns[internalColumnIndex][rowIndex];
}

DatatableEntry::operator int32_t&()
{
	return table->intColumns[internalColumnIndex][rowIndex];
}
