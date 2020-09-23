#pragma once
#include "../Time/FDuration.h"

struct FAudioClip
{
	// To-Do: Add Implementation
	int sampleRate;
	int frequency;
	float* data;

	FDuration GetDuration() const;
};