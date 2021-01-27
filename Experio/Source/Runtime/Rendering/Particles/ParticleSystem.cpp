#include "ParticleSystem.h"
#include "../Shaders/ShaderReader.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../VertexArray.h"
#include "../../Camera/CameraSystem.h"
#include "../../Core/Window.h"
#include "../../Core/LWindowOperations.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../../Math/LMath.h"
#include "../../Debug/Profiler.h"

int particlesPerSecond = 10000;

ParticleSystem::ParticleSystem(GameObject * object)
{
	this->gameObject = object;
	Start();
}

ParticleSystem::~ParticleSystem()
{
	delete[] particles;
	delete particleShader;
}

void ParticleSystem::Start()
{
	maxParticles = GetMaxParticles();
	particles = new FParticleData[maxParticles];
	particleShader = ShaderReader::ReadShader(
		"C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Particle.shader"
	);
}

void ParticleSystem::Update()
{
	PROFILE_SCOPE("Particle Update");

	int newParticles = (int)(particlesPerSecond * GameTime::deltaTime);
	FVector3 mainDirection = FVector3(0, 10.0f, 0.0f);
	float spread = 1.5f;

	FVector3* particlePositions = new FVector3[maxParticles];
	FColor* particleColors = new FColor[maxParticles];
	
	// Add new particles
	int particleIndex;
	for (int i = 0; i < newParticles; i++)
	{
		particleIndex = FindUnusedParticle();
		particles[particleIndex].life = 5.0f;
		particles[particleIndex].position = gameObject->GetPosition();

		FVector3 randomDirection = FVector3(
			(rand() % 2000 - 1000.0f) / 1000.0f, 
			(rand() % 2000 - 1000.0f) / 1000.0f, 
			(rand() % 2000 - 1000.0f) / 1000.0f
		);
		particles[particleIndex].speed = mainDirection + randomDirection * spread;

		particles[particleIndex].color = FColor::RandomColor(false);
	}

	int particlesCount = 0;
	for (int i = 0; i < maxParticles; i++)
	{
		FParticleData& p = particles[i];
		
		if (p.life > 0.0f)
		{
			p.life -= GameTime::deltaTime;

			if (p.life > 0.0f)
			{
				p.speed += FVector3(0.0f, -9.81f, 0.0f) * (float)GameTime::deltaTime * 0.5f;
				p.position += p.speed * (float)GameTime::deltaTime;
				
				particlePositions[particlesCount] = p.position;
				particleColors[particlesCount] = p.color;
			}
			else
			{

			}
			particlesCount++;
		}
	}

	// Add Particle Sorting
	
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	GLenum error = glGetError();

	glm::mat4 viewMatrix = CameraSystem::Get()->currentViewMatrix;
	FWindowData data = Window::GetWindowData();
	float aspectRatio = LWindowOperations::GetAspectRatio(data);
	glm::mat4 projectionMatrix = CameraSystem::Get()->currentProjectionMatrix;

	particleShader->Bind();
	particleShader->SetUniformMatrix4("VP", projectionMatrix * viewMatrix);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint positionBuffer;
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, particlesCount * sizeof(FVector3), particlePositions, GL_STATIC_DRAW);

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, particlesCount * sizeof(FColor), particleColors , GL_STATIC_DRAW);

	FParticleData tempParticle = particles[3];

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size : x + y + z => 3
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		4,                                // size : r + g + b + a => 4
		GL_FLOAT,						  // type
		GL_TRUE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad                                  -> 1

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 36, particlesCount);
	error = glGetError();

	glDeleteVertexArrays(1, &vertexArray);
}

int ParticleSystem::FindUnusedParticle()
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

unsigned int ParticleSystem::GetMaxParticles() const
{
	// ADD CALCULATIONS HERE
	return 100000;
}
