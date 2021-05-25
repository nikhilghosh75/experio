#include "ParticleComponent.h"
#include "ParticleReader.h"
#include "../Shaders/ShaderReader.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../VertexArray.h"
#include "../Renderer.h"
#include "../../Camera/CameraSystem.h"
#include "../../Core/Window.h"
#include "../../Core/LWindowOperations.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../../Math/LMath.h"
#include "../../Debug/Profiler.h"

int particlesPerSecond = 10000;

ParticleComponent::ParticleComponent(GameObject* object)
{
	this->gameObject = object;

	particles = nullptr;
	particlePositions = nullptr;
	particleColors = nullptr;
}

ParticleComponent::~ParticleComponent()
{
	delete[] particles;
	delete[] particleColors;
	delete[] particlePositions;

	delete particleShader;
}

void ParticleComponent::Start()
{
	particleSystem = ParticleReader::ReadParticleSystem(
		"C:/Users/debgh/source/repos/experio/Demo Project/Assets/Art/Particles/Particle.pbprtcle"
	);

	maxParticles = particleSystem.maxCount;
	particles = new FParticleData[maxParticles];

	particleColors = new FColor[maxParticles];
	particlePositions = new FVector3[maxParticles];

	particleShader = ShaderReader::ReadShader(
		"C:/Users/debgh/source/repos/experio/Experio/Resources/Standard/Shaders/Particle.shader"
	);
	particleMesh = MeshManager::LoadMesh(
		"C:/Users/debgh/source/repos/experio/Demo Project/Assets/Meshes/cube-normalized.obj"
	);

	particleTime = 0;

	particleSystem.Start(*this);
}

void ParticleComponent::Update()
{
	PROFILE_SCOPE("Particle Update");

	CheckForNull();

	particleTime += GameTime::deltaTime;

	particleSystem.Update(*this);

	unsigned int numParticles = PopulateVectors();
	DrawParticles(numParticles);
}

void ParticleComponent::CheckForNull()
{
	if (particles == nullptr)
		particles = new FParticleData[maxParticles];

	if (particleColors == nullptr)
		particleColors = new FColor[maxParticles];

	if (particlePositions == nullptr)
		particlePositions = new FVector3[maxParticles];
}

int ParticleComponent::FindUnusedParticle()
{
	for (int i = lastUsedParticle; i < maxParticles; i++) {
		if (particles[i].life < 0) {
			lastUsedParticle = i;
			return i;
		}
	}

	for (int i = 0; i < lastUsedParticle; i++) {
		if (particles[i].life < 0) {
			lastUsedParticle = i;
			return i;
		}
	}

	return 0;
}

unsigned int ParticleComponent::PopulateVectors()
{
	unsigned int particlesCount = 0;
	for (int i = 0; i < maxParticles; i++)
	{
		FParticleData& p = particles[i];
		p.life -= GameTime::deltaTime;

		if (p.life > 0.0f)
		{
			p.speed += FVector3(0.0f, -9.81f, 0.0f) * (float)GameTime::deltaTime * 0.5f;
			p.position += p.speed * (float)GameTime::deltaTime;

			particlePositions[particlesCount] = p.position;
			particleColors[particlesCount] = p.color;
			particlesCount++;
		}
	}

	return particlesCount;
}

void ParticleComponent::SetUniforms()
{
	glm::mat4 viewMatrix = Renderer::Get()->GetViewMatrix();
	glm::mat4 projectionMatrix = Renderer::Get()->GetProjectionMatrix();
	glm::mat4 vp = projectionMatrix * viewMatrix;

	particleShader->Bind();
	particleShader->SetUniformMatrix4("VP", vp);
}

void ParticleComponent::AddVertexBuffer(VertexArray& va)
{
	VertexBufferLayout vertexLayout;
	vertexLayout.PushFloat(3);
	va.AddBuffer(particleMesh->verticies, vertexLayout, 0);
}

void ParticleComponent::AddPositionBuffer(VertexArray& va, unsigned int particleCount)
{
	VertexBuffer positions(particlePositions, sizeof(FVector3) * particleCount, false);
	VertexBufferLayout positionLayout;
	positionLayout.PushFloat(3);
	va.AddBuffer(&positions, positionLayout, 1);
}

void ParticleComponent::AddColorBuffer(VertexArray& va, unsigned int particleCount)
{
	VertexBuffer colors(particleColors, sizeof(FColor) * particleCount, false);
	VertexBufferLayout colorLayout;
	colorLayout.PushFloat(4, true);
	va.AddBuffer(&colors, colorLayout, 1);
}

void ParticleComponent::DrawParticles(unsigned int particleCount)
{
	SetUniforms();

	VertexArray va;

	AddVertexBuffer(va);
	AddPositionBuffer(va, particleCount);
	AddColorBuffer(va, particleCount);

	Renderer::Get()->SetDepthTesting(true);

	unsigned int numTriangles = particleMesh->verticies->GetCount();
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, numTriangles, particleCount);
}


void ParticleComponent::SpawnParticles(unsigned int numParticles)
{
	for (unsigned int i = 0; i < numParticles; i++)
	{
		int particleIndex = FindUnusedParticle();
		particles[particleIndex].life = particleSystem.defaultLifetime;
		particles[particleIndex].position = gameObject->GetPosition();
	}
}

unsigned int ParticleComponent::GetMaxParticles() const
{
	// ADD CALCULATIONS HERE
	return 100000;
}

float ParticleComponent::GetParticleTime() const
{
	return 0.0f;
}
