#pragma once

#include <Evil.h>

#include "Random.h"

#include "ParticleSystem.h"

#include <glm/glm.hpp>

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Evil::Timestep ts);
	void OnRender();

	void Reset();

	float GetRotation() const { return glm::radians(m_VelocityY * 4.0f - 90.0f); }
	const glm::vec2& GetPosition() const { return m_Position; }
	const glm::mat4& GetTransform() const { return m_Trasform; }

	void UpdateParticles(Evil::Timestep ts) { m_ParticleSystem.OnUpdate(ts); }
private:
	void CalculateTransform();
	bool ActiveEngine() const;

	glm::vec2 m_Position = { 0.0f, 0.0f };
	float m_VelocityY = 0.0f;
	glm::mat4 m_Trasform{ 1.0f };

	float m_EnginePower = 0.5f;
	float m_Gravity = 0.4f;

	uint32_t m_MaxParticles = 5000;
	ParticleSystem m_ParticleSystem;

	ParticleProps m_SmokeParticle, m_EngineParticle;
	float m_Time = 0.0f;
	float m_SmokeEmitInterval = 0.4f;

	Evil::Ref<Evil::Texture2D> m_SpaceShipSprite;
};
