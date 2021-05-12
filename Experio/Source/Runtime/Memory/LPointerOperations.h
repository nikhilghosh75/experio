#pragma once
#include <cstdint>

class LPointerOperations
{
public:
	static void* Add(void* p, size_t x);

	/*
	static void* AlignForward(void* address, uint8_t alignment);

	static uint8_t AlignForwardAdjustment(void* address, uint8_t alignment);

	static uint8_t AlignForwardAdjustmentWithHeader(void* address, uint8_t alignment, uint8_t headerSize);

	static size_t CalculatePadding(size_t baseAddress, size_t alignment);
	*/
};