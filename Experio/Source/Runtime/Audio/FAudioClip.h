#pragma once
#include "../Time/FDuration.h"

struct FAudioClip
{
	// To-Do: Add Implementation
	uint32_t sampleRate;
	uint32_t numSamples;
	float* data;

	FDuration GetDuration() const;
};