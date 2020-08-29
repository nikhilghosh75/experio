#include <cstdint>
#include "LPointerOperations.h"

/*
void* LPointerOperations::AlignForward(void * address, uint8_t alignment)
{
	return (void*)( (reinterpret_cast<uint8_t*>(address) + static_cast<uint8_t>(alignment - 1) ) & static_cast<uint8_t>(~(alignment - 1)));
}
*/

uint8_t LPointerOperations::AlignForwardAdjustment(void* address, uint8_t alignment)
{
	uint8_t* newAlignment = &alignment;
	newAlignment--;
	uint8_t newAddress = *reinterpret_cast<uint8_t*>(address);
	uint8_t adjustment = alignment - (newAddress & *newAlignment);

	if (adjustment == alignment)
	{
		return 0;
	}

	return adjustment;
}

uint8_t LPointerOperations::AlignForwardAdjustmentWithHeader(void* address, uint8_t alignment, uint8_t headerSize)
{
	uint8_t adjustment = AlignForwardAdjustment(address, alignment);
	uint8_t neededSpace = headerSize;

	if (adjustment < neededSpace)
	{
		neededSpace -= adjustment;

		adjustment += alignment * (neededSpace / alignment);

		if (neededSpace % alignment > 0)
		{
			adjustment += alignment;
		}
	}
	return adjustment;
}

void* LPointerOperations::Add(void* p, size_t x)
{
	return (void*)(reinterpret_cast<uintptr_t>(p) + x);
}

size_t LPointerOperations::CalculatePadding(size_t baseAddress, size_t alignment)
{
	size_t multiplier = (baseAddress / alignment) + 1;
	size_t alignedAddress = multiplier * alignment;
	size_t padding = alignedAddress - baseAddress;
	return padding;
}