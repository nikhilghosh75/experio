#pragma once
#include <functional>
#include <initializer_list>

template<typename T, typename Comp = std::less<T>>
class THeap
{
	Comp comp;

	T* data;
	uint32_t count;
	uint32_t capacity;

public:
	THeap()
	{
		count = 0;
		data = (T*) ::operator new(3 * sizeof(T));
		capacity = 3;
	}

	THeap(std::initializer_list<T> list)
	{

	}

	void Insert(const T& item)
	{
		if (count == capacity - 2)
		{
			Grow();
		}

		data[count + 1] = item;

		uint32_t index = count + 1;
		while (index > 1)
		{
			if (this->comp(data[index / 2], data[index]))
				Swap(index, index / 2);
			else
				break;

			index /= 2;
		}

		count++;
	}

	template<typename ... Args>
	void Emplace(Args&& ... args)
	{
		if (count == capacity - 2)
		{
			Grow();
		}
		data[count + 1] = T(std::forward<Args>(args)...);

		uint32_t index = count + 1;
		while (index > 1)
		{
			if (this->comp(data[index / 2], data[index]))
				Swap(index, index / 2);
			else
				break;

			index /= 2;
		}

		count++;
	}

	void Grow()
	{
		uint32_t newCapacity = capacity * 1.5;
		T* newData = (T*) ::operator new(newCapacity * sizeof(T));

		for (int i = 0; i < count + 1; i++)
		{
			newData[i] = std::move(data[i]);
		}

		::operator delete(this->data, this->capacity * sizeof(T));
		this->data = newData;
		this->capacity = newCapacity;
	}

	const T& First() const
	{
		return data[1];
	}

	T Pop()
	{
		T elem = data[1];
		Swap(count, 1);
		count--;
		
		uint32_t index = 2;
		while (index < count + 1)
		{
			if (index < count && this->comp(data[index], data[index + 1]))
			{
				index++;
			}

			if (this->comp(data[index / 2], data[index]))
				Swap(index, index / 2);
			else
				break;

			index *= 2;
		}
		return elem;
	}

	void Empty()
	{
		for (uint32_t i = 0; i < this->count; i++)
		{
			data[i + 1].~T();
		}
		this->count = 0;
	}

	uint32_t Count() { return count; }
	uint32_t Capacity() { return capacity; }

private:
	void Swap(uint32_t a, uint32_t b)
	{
		T temp = data[a];
		data[a] = data[b];
		data[b] = temp;
	}
};