#include "TMatrix.h"

template<short rows, short columns, class T>
TMatrix<rows, columns, T>::TMatrix(T * value)
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

template<short rows, short columns, class T>
TMatrix<rows, columns, T>::TMatrix(std::vector<T> values)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			elements[i][j] = values[i * rows + j];
		}
	}
}
