#pragma once

// MOVE LATER
struct Datatable
{
	unsigned int rowCount;
	unsigned int columnCount;

	unsigned int GetCount() const { return rowCount * columnCount; }
};