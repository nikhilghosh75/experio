#pragma once

enum class ERandomGeneratorType
{
	CRandom,
	LinearCongruential,
	MerceneTwister,
	TrueRandom
};

class Random
{
public:
	static float Rand(ERandomGeneratorType generator = ERandomGeneratorType::CRandom);

	static float RandomInRange(float start, float end, ERandomGeneratorType generator = ERandomGeneratorType::CRandom);
	static int RandomIntInRange(int start, int end, ERandomGeneratorType generator = ERandomGeneratorType::CRandom);
};