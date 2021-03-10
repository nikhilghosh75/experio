#pragma once
#include "../Time/FDuration.h"

/// <summary>
/// Represents a piece of audio as the actual data
/// </summary>

struct FAudioClip
{
	// To-Do: Add Implementation
	uint32_t sampleRate;
	uint32_t numSamples;
	float* data;

	FDuration GetDuration() const;
};