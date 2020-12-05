#pragma once
#include <stdint.h>

class Range
{
	int64_t start;
	int64_t stop;
	int64_t step;

	Range(int64_t stop)
	{
		this->start = 0;
		this->stop = stop;
		this->step = 1;
	}

	Range(int64_t start, int64_t stop)
	{
		this->start = start;
		this->stop = stop;
		this->step = 1;
	}

	Range(int64_t start, int64_t stop, int64_t step)
	{
		this->start = start;
		this->stop = stop;
		this->step = step;
	}

	class Iterator
	{
		int64_t current;
		int64_t stop;
		int64_t step;

	public:
		Iterator(int64_t start, int64_t stop, int64_t step)
		{
			this->current = start;
			this->stop = stop;
			this->step = step;
		}

		int64_t operator*() const
		{
			return this->current;
		}

		Iterator& operator++()
		{
			this->current += this->step;
			return *this;
		}

		Iterator& operator++(int)
		{
			Iterator result(this->current, this->stop, this->step);
			++(*this);
			return result;
		}

		bool operator==(const Iterator& other) const
		{
			if (other.current >= other.stop && this->current >= this->stop)
			{
				return true;
			}
			return other.current == this->current;
		}

		bool operator==(const Iterator& other) const
		{
			if (other.current < other.stop || this->current < this->stop)
			{
				return false;
			}
			return other.current != this->current;
		}
	};

	Iterator begin() const
	{
		return Iterator(this->start, this->stop, this->step);
	}

	Iterator end() const
	{
		return Iterator(1, 0, 0);
	}
};