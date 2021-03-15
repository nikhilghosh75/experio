#pragma once
#include "Particle.h"
#include "../Shaders/Shader.h"
#include "../../Framework/Framework.h"

class ParticleComponent : public Component
{
	FParticleData* particles;
	unsigned int maxParticles;
	int lastUsedParticle = 0;
	Shader* particleShader;

public:
	ParticleComponent() {};
	ParticleComponent(GameObject* object);

	~ParticleComponent();

	virtual void Start() override;

	virtual void Update() override;

private:
	int FindUnusedParticle();

	unsigned int GetMaxParticles() const;
};