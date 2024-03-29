#pragma once
#include <stdint.h>
#include "GameObject.h"

/// <summary>
/// A wrapper over a 64-bit integer that represents a mask for layers
/// Layers can only be between 0 and 63 (inclusive)
/// </summary>

struct Layermask
{
	uint64_t mask;

	operator unsigned long long() { return mask; }

	Layermask()
	{
		this->mask = 0;
	}

	Layermask(uint64_t mask)
	{
		this->mask = mask;
	}

	bool CompareLayer(uint8_t layer) const
	{
		return (mask & (1 << layer)) != 0;
	}

	bool CompareLayer(GameObject object) const
	{
		return CompareLayer(object.layer);
	}

	void SetBitTrue(uint8_t bit)
	{
		this->mask = this->mask | (1 << bit);
	}

	void SetBitFalse(uint8_t bit)
	{
		this->mask = this->mask & (~(1 << bit));
	}

	void SetBitsTrue(uint8_t start = 0, uint8_t end = 64)
	{
		for (uint8_t i = start; i < end; i++)
		{
			this->mask = this->mask | (1 << i);
		}
	}

	void SetBitsFalse(uint8_t start = 0, uint8_t end = 64)
	{
		for (uint8_t i = start; i < end; i++)
		{
			this->mask = this->mask & (~(1 << i));
		}
	}

	static Layermask AND(Layermask L1, Layermask L2)
	{
		return Layermask(L1.mask & L2.mask);
	}

	// Change Name Later
	void FillBoolArray(bool* arr) const
	{
		for (uint8_t i = 0; i < 64; i++)
		{
			arr[i] = CompareLayer(i);
		}
	}
};