#pragma once
#include "Particle.h"
#include "ParticleSystem.h"
#include "../Shaders/Shader.h"
#include "../../Framework/Framework.h"
#include "../Managers/MeshManager.h"

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
	MeshRef particleMesh;

	ParticleComponent() {};
	ParticleComponent(GameObject* object);

	ParticleComponent& operator=(const ParticleComponent& component) = default;

	~ParticleComponent();

	virtual void Start() override;

	virtual void Update() override;

	void SpawnParticles(unsigned int numParticles);

private:
	FColor* particleColors;
	FVector3* particlePositions;

	int FindUnusedParticle();

	void CheckForNull();

	unsigned int PopulateVectors();

	void SetUniforms();

	void AddVertexBuffer(VertexArray& va);
	void AddPositionBuffer(VertexArray& va, unsigned int particleCount);
	void AddColorBuffer(VertexArray& va, unsigned int particleCount);

	void DrawParticles(unsigned int particleCount);

public:
	unsigned int GetMaxParticles() const;

	float GetParticleTime() const;
};