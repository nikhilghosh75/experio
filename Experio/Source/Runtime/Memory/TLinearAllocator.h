#pragma once
#include "TAllocator.h"
#include "LPointerOperations.h"
#include <cstddef>

/*
template <class T> 
class TLinearAllocator : public TAllocator<T>
{
public:
	TLinearAllocator()
	{
		this->memoryUsed = 0;
		this->allocationsMade = 0;
		this->start = nullptr;
	}

	TLinearAllocator(size_t size)
	{
		this->totalSize = size;
		this->memoryUsed = 0;
		this->allocationsMade = 0;

		this->start = malloc(size); // Change Later
	}

	TLinearAllocator(void* start, size_t size)
	{
		this->start = start;
		this->totalSize = size;
		this->memoryUsed = 0;
		this->allocationsMade = 0;
	}

	~TLinearAllocator()
	{
		if (this->start != nullptr)
		{
			delete this->start;
		}
	}

	void* Allocate(size_t size, uint8_t alignment) override
	{
		size_t padding = 0;
		size_t paddedAddress = 0;
		size_t currentAddress = (size_t)this->start + this->offset;

		if (alignment != 0 && this->memoryUsed % alignment != 0)
		{
			// Alignment is required. Find the next aligned memory address and update offset
			padding = LPointerOperations::CalculatePadding(currentAddress, alignment);
		}

		if (this->offset + padding + size > this->totalSize)
		{
			return nullptr;
		}

		this->offset += padding;
		size_t nextAddress = currentAddress + padding;
		this->offset += size;
		this->allocationsMade++;
		this->memoryUsed = offset;

		return (void*)nextAddress;
	}

	void Deallocate(void* p) override
	{
		// TO-DO: Create actual exceptions
		throw "Deallocate() invalid with Linear Allocator. Use clear() instead";
	}

	void Init() override
	{
		if (this->start == nullptr)
		{
			this->start = malloc(this->totalSize);
		}

		this->offset = 0;
	}

	void Clear()
	{
		this->allocationsMade = 0;
		this->memoryUsed = 0;
		this->currentPosition = this->start;
		this->offset = 0;
	}

private:
    void* currentPosition;
    size_t offset;
};
*/