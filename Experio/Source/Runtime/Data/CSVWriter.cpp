#include "CSVWriter.h"
#include <fstream>

void CSVWriter::SaveToCSV(Datatable& datatable, const std::string& filepath)
{
	std::ofstream outFile(filepath);

	for (uint32_t i = 0; i < datatable.ColumnCount(); i++)
	{
		outFile << datatable.GetColumn(i).ColumnName() << ", ";
	}
	outFile << std::endl;

	for (uint32_t i = 0; i < datatable.RowCount(); i++)
	{
		for (uint32_t j = 0; j < datatable.ColumnCount(); j++)
		{
			DatatableEntry entry = datatable[i][j];
			switch (entry.ColumnType())
			{
			case EDataColumnType::INT:
				outFile << (int32_t)entry << std::endl;
				break;
			case EDataColumnType::FLOAT:
				outFile << (float)entry << std::endl;
				break;
			case EDataColumnType::STRING:
				outFile << (std::string)entry << std::endl;
				break;
			}
			
			if (j != datatable.ColumnCount() - 1)
			{
				outFile << ", ";
			}
		}
		outFile << std::endl;
	}
}
