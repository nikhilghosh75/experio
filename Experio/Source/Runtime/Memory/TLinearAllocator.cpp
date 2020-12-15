#include "LPointerOperations.h"
#include <cstddef>
#include <iostream>
#include "TLinearAllocator.h"

void TestLinearAllocator()
{
	/*
	TLinearAllocator<int>* allocator = new TLinearAllocator<int>((size_t)400);
	allocator->Init();
	int* testArray;
	testArray = (int*)allocator->Allocate(4, alignof(int));
	testArray[0] = 1;
	testArray[1] = 3;

	std::cout << testArray[1] << std::endl;
	*/
}
