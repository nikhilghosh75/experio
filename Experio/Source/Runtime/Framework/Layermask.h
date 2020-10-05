#pragma once
#include <stdint.h>
#include "GameObject.h"

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