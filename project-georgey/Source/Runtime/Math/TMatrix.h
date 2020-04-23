#pragma once
#include <vector>

template <short rows, short columns, class T>
class TMatrix
{
public:

	TMatrix(T* value);
	TMatrix(std::vector<T> values);

	// String Operator

	T elements[columns][rows];
};
