#pragma once
#include "Particle.h"
#include "../Shaders/Shader.h"
#include "../../Framework/Framework.h"

class ParticleSystem : public Component
{
	FParticleData* particles;
	unsigned int maxParticles;
	int lastUsedParticle = 0;
	Shader* particleShader;

public:
	ParticleSystem() {};
	ParticleSystem(GameObject* object);

	~ParticleSystem();

	virtual void Start() override;

	virtual void Update() override;

private:
	int FindUnusedParticle();

	unsigned int GetMaxParticles() const;
};