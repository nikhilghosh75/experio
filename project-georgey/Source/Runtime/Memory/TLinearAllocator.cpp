#include "LPointerOperations.h"
#include <cstddef>
#include <iostream>
#include "TLinearAllocator.h"

void Test()
{
	TLinearAllocator<int>* allocator = new TLinearAllocator<int>((size_t)400);
	allocator->Init();
	int* testArray;
	testArray = (int*)allocator->Allocate(4, alignof(int));
	testArray[0] = 1;
	testArray[1] = 3;

	std::cout << testArray[1] << std::endl;
}

template<class T>
TLinearAllocator<T>::TLinearAllocator()
{
	this->memoryUsed = 0;
	this->allocationsMade = 0;
}

template<class T>
TLinearAllocator<T>::TLinearAllocator(size_t size) 
{
	this->totalSize = size;
    this->memoryUsed = 0;
    this->allocationsMade = 0;

	this->start = nullptr;
}

template<class T>
TLinearAllocator<T>::TLinearAllocator(size_t size, void* start)
{
	this->start = start;
    this->totalSize = size;
    this->memoryUsed = 0;
    this->allocationsMade = 0;

	if (size <= 0)
	{
		// TO-DO: Add Error
	}

	currentPosition = start;
}

template<class T>
TLinearAllocator<T>::~TLinearAllocator()
{
	currentPosition = nullptr;
}

template<class T>
void * TLinearAllocator<T>::Allocate(size_t size, uint8_t alignment)
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

    return (void*) nextAddress;
}

template<class T>
void TLinearAllocator<T>::Deallocate(void * p)
{
	throw "Deallocate() invalid with Linear Allocator. Use clear() instead";
}

template<class T>
void TLinearAllocator<T>::Init()
{
	if(this->start != nullptr)
	{
		free(this->start);
	}
	this->start = malloc(this->totalSize);
}

template<class T>
void TLinearAllocator<T>::Clear()
{
	this->allocationsMade = 0;
	this->memoryUsed = 0;
	currentPosition = this->start;
}
