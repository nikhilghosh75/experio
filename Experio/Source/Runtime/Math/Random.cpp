#include "Random.h"
#include <cstdlib>

#define LCG_M 2147483647 
#define LCG_A 16807
#define LCG_C 0

static int LCG_Seed = 3116;

float Random::Rand(ERandomGeneratorType generator)
{
	switch (generator)
	{
	case ERandomGeneratorType::CRandom:
		return (float)rand() / RAND_MAX;
	case ERandomGeneratorType::LinearCongruential:
		LCG_Seed = (LCG_Seed * LCG_A + LCG_C) % LCG_M;
		return ((float)LCG_Seed) / LCG_M;
	}
	return 0;
}

float Random::RandomInRange(float start, float end, ERandomGeneratorType generator)
{
	switch (generator)
	{
	case ERandomGeneratorType::CRandom:
		return start + (float)rand() / (end - start);
	case ERandomGeneratorType::LinearCongruential:
		LCG_Seed = (LCG_Seed * LCG_A + LCG_C) % LCG_M;
		return start + ((float)LCG_Seed) / (end - start);
	}
	return 0;
}

int Random::RandomIntInRange(int start, int end, ERandomGeneratorType generator)
{
	return (int)RandomInRange(start, end, generator);
}
