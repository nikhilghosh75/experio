#pragma once
#include <stdint.h>

/// <summary>
/// An array that only exists on the stack but functions like a TArray
/// Using this avoids a heap allocation
/// </summary>

template<typename T, uint32_t N>
class TStackArray
{
	size_t count;
	T data[N];
public:
	TStackArray()
	{
		count = 0;
	}

	TStackArray(const T& object, uint32_t num)
	{
		if (num > N)
			num = N;
		for (uint32_t i = 0; i < num; i++)
		{
			data[i] = object;
		}
		this->count = num;
		this->capacity = num;
	}

	void Append(const T& object)
	{
		if (this->count >= N) return;
		this->data[this->count] = object;
		this->count++;
	}

	void Append(const T* objects, uint32_t count)
	{
		if (this->count + count >= N) return;
		for (uint32_t i = 0; i < count; i++)
		{
			this->data[this->count + i] = objects[i];
		}
		this->count += count;
	}

	template<typename ... Args>
	T& EmplaceAppend(Args&& ... args)
	{
		if (this->count >= N) return this->data[this->count - 1];
		this->data[this->count] = T(std::forward<Args>(args) ...);
		this->count++;
		return this->data[this->count - 1];
	}

	void Empty()
	{
		for (uint32_t i = 0; i < this->count; i++)
		{
			data[i].~T();
		}
		this->count = 0;
	}

	void RemoveAt(uint32_t index)
	{
		this->data[index].~T();
		for (uint32_t i = index + 1; i < this->count; i++)
		{
			data[i - 1] = data[i];
		}
		this->count--;
	}

	void RemoveBack()
	{
		this->count--;
		this->data[this->count].~T();
	}

	void Fill(const T& element)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			data[i] = element;
		}
	}

	uint32_t Count() const { return count; }
	uint32_t Capacity() const { return N; }

	T& operator[](uint32_t index) { return data[index]; }
	const T& operator[](uint32_t index) const { return data[index]; }

	T* Data() const { return data; }
};