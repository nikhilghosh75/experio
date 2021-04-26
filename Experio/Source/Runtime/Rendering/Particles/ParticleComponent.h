#pragma once
#include "Particle.h"
#include "ParticleSystem.h"
#include "../Shaders/Shader.h"
#include "../../Framework/Framework.h"

class ParticleComponent : public Component
{
	FParticleData* particles;
	unsigned int maxParticles;
	int lastUsedParticle = 0;
	float particleTime;
	unsigned int numIterations;

	friend class ParticleSystem;

public:
	Shader* particleShader;
	ParticleSystem particleSystem;

	ParticleComponent() {};
	ParticleComponent(GameObject* object);

	~ParticleComponent();

	virtual void Start() override;

	virtual void Update() override;

	void SpawnParticles(unsigned int numParticles);

private:
	int FindUnusedParticle();

public:
	unsigned int GetMaxParticles() const;
};