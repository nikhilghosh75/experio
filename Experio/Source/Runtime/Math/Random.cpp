#include "Random.h"
#include "../Core/Window.h"
#include "../Input/Input.h"
#include <cstdlib>

#define LCG_M 2147483647 
#define LCG_A 16807
#define LCG_C 0

static int LCG_Seed = 3116;

std::mt19937 Random::mersenneTwister;
std::mt19937_64 Random::mersenneTwister64;

void Random::Initialize()
{

}

float Random::Rand(ERandomGeneratorType generator)
{
	switch (generator)
	{
	case ERandomGeneratorType::CRandom:
		return (float)rand() / RAND_MAX;
	case ERandomGeneratorType::LinearCongruential:
		LCG_Seed = (LCG_Seed * LCG_A + LCG_C) % LCG_M;
		return ((float)LCG_Seed) / LCG_M;
	case ERandomGeneratorType::MersenneTwister:
		return (float)mersenneTwister() / mersenneTwister.max();
	case ERandomGeneratorType::TrueRandom:
		return fmodf(Rand(ERandomGeneratorType::LinearCongruential)
			+ Window::GetWindowData().height * 0.001f + Input::GetMousePosition().y * 0.01f, 1);
	}
	return 0;
}

float Random::RandomInRange(float start, float end, ERandomGeneratorType generator)
{
	switch (generator)
	{
	case ERandomGeneratorType::CRandom:
		return start + ((float)rand() / RAND_MAX) * (float)(end - start);
	case ERandomGeneratorType::LinearCongruential:
		LCG_Seed = (LCG_Seed * LCG_A + LCG_C) % LCG_M;
		return start + (((float)LCG_Seed) / (float)LCG_M) * (end - start);
	case ERandomGeneratorType::MersenneTwister:
		return start + (float)mersenneTwister() / (end - start);
	}
	return start + Rand(generator) * (end - start);
}

int Random::RandomIntInRange(int start, int end, ERandomGeneratorType generator)
{
	return (int)RandomInRange(start, end, generator);
}

unsigned int Random::RandomUIntInRange(unsigned int start, unsigned int end, ERandomGeneratorType generator)
{
	return (unsigned int)RandomInRange(start, end, generator);
}
