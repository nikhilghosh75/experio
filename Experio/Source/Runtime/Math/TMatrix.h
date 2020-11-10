#pragma once
#include <vector>

template <short rows, short columns, class T>
class TMatrix
{
public:
	TMatrix()
	{
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				elements[i][j] = 0;
			}
		}
	}

	TMatrix(T elem)
	{
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				elements[i][j] = elem;
			}
		}
	}

	TMatrix(T* value)
	{
		size_t typeSize = sizeof(T);
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				elements[i][j] = (T)((void*)value + (void*)((i * rows + j) * typeSize));
			}
		}
	}

	TMatrix(std::vector<T> values)
	{
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				elements[i][j] = values[i * rows + j];
			}
		}
	}

	// String Operator

	short Rows() const { return rows; }
	short Columns() const { return columns; }
	short NumElements() const { return rows * columns; }

	T elements[columns][rows];
};

template<short dimensions, typename T>
class TSquareMatrix : public TMatrix<dimensions, dimensions, T>
{
	short Dimensions() const { return dimensions; }
};