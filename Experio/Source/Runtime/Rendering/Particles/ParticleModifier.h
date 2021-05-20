#pragma once
#include "Particle.h"
#include "../../Math/Bezier.h"
#include <vector>

class ParticleComponent;

// Default Particle Modifiers:

class ParticleModifier
{
public:
	bool isActive = true;

	virtual void Update(FParticleData& particle) = 0;
};

enum class EParticleModifierType
{
	None = 0,
	SizeOverLife = 10,
	ColorOverLife = 11,
	VelocityOverLife = 12,
	GravityOverLife = 13
};

class SizeOverLife : public ParticleModifier
{
public:
	Bezier sizeXCurve;
	Bezier sizeYCurve;
	Bezier sizeZCurve;

	virtual void Update(FParticleData& particle) override;
};

class ColorOverLife: public ParticleModifier
{
public:
	Bezier redCurve;
	Bezier greenCurve;
	Bezier blueCurve;

	virtual void Update(FParticleData& particle) override;
};

class VelocityOverLife : public ParticleModifier
{
public:
	Bezier speedXCurve;
	Bezier speedYCurve;
	Bezier speedZCurve;

	virtual void Update(FParticleData& particle) override;
};

class GravityOverLife : public ParticleModifier
{
public:
	Bezier gravityCurve;

	virtual void Update(FParticleData& particle) override;
};

// Particle Modifier that only affects the start
class StartParticleModifier
{
public:
	bool isActive = true;

	virtual void OnStart(ParticleComponent& component) = 0;
};

class SpawnAtStart : public StartParticleModifier
{
public:
	bool isActive = true;

	unsigned int numToSpawn;

	virtual void OnStart(ParticleComponent& component) override;
};

enum class ESpawnMode
{
	None,
	OverLife,
	Burst
};

struct FBurstPoint
{
	float time;
	unsigned int num;
};

struct FBurstSpawnInfo
{
	std::vector<FBurstPoint> times;
	int currentTime;
};

class SpawnModifier
{
public:
	ESpawnMode mode;

	union
	{
		Bezier spawnCurve; // Used in SpawnOverLife
		FBurstSpawnInfo burstSpawnInfo; // Used in Burst
	};

	SpawnModifier();

	~SpawnModifier();

	void Update(ParticleComponent& component);

	void UpdateOverLife(ParticleComponent& component);

	void UpdateBurst(ParticleComponent& component);
};