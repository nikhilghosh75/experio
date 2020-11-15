#pragma once
#include <stdint.h>

template<typename T, uint32_t N>
class TStackArray
{
	T data[N];
public:
	TStackArray() {}

	void Fill(const T& element)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			data[i] = element;
		}
	}

	uint32_t Count() const { return N; }

	T& operator[](uint32_t index) { return data[index]; }
	const T& operator[](uint32_t index) const { return data[index]; }

	T* Data() const { return data; }
};