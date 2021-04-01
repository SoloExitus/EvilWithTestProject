#pragma once

#include <Evil.h>

struct ParticleProps
{
	glm::vec3 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(uint32_t maxParticle);

	void Emit(const ParticleProps& particleProps);

	void OnUpdate(Evil::Timestep ts);
	void OnRender();
private:
	struct Particle
	{
		glm::vec3 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};

	std::vector<Particle> m_ParticlePool;
	int m_PoolIndex = 0;
};
