#pragma once
#include <random>

enum class ERandomGeneratorType
{
	CRandom,
	LinearCongruential,
	MersenneTwister,
	TrueRandom
};

class Application;

class Random
{
	friend class Application;
	static void Initialize();

	static std::mt19937 mersenneTwister;
	static std::mt19937_64 mersenneTwister64;

public:
	// 0 - 1
	static float Rand(ERandomGeneratorType generator = ERandomGeneratorType::CRandom);

	static float RandomInRange(float start, float end, ERandomGeneratorType generator = ERandomGeneratorType::CRandom);
	static int RandomIntInRange(int start, int end, ERandomGeneratorType generator = ERandomGeneratorType::CRandom);
	static unsigned int RandomUIntInRange(unsigned int start, unsigned int end, ERandomGeneratorType generator = ERandomGeneratorType::CRandom);
};