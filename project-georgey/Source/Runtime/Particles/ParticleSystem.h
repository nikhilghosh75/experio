#pragma once
#include "Particle.h"
#include "../Rendering/Shader.h"

class ParticleSystem
{
	FParticleData* particles;
	unsigned int maxParticles;
	int lastUsedParticle;
	Shader* particleShader;

public:
	ParticleSystem();

	~ParticleSystem();

	void Initialize();

	void Update();

private:
	int FindUnusedParticle();

	unsigned int GetMaxParticles() const;
};