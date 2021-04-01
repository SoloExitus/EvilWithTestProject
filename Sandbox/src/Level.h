#pragma once

#include "Player.h"

struct Pillar
{
	bool New = true;

	float PositionX = 0.0f;
	float TopPositionY = -10.0f;
	float BottomPositionY = 10.0f;

	//float TargetTopPositionY = -10.0f;
	//float TargetBottomPositionY = 10.0f;

	glm::vec2 Scale = { 15.0f, 20.0f };
};

class Level
{
public:
	void Init();

	void OnUpdate(Evil::Timestep ts);
	void OnRender();

	bool IsGameOver() const { return m_GameOver; }
	void Reset();

	uint32_t GetScore() { return m_Score; }
	Player& GetPlayer() { return m_Player; }
private:
	void SetRandomPillar(Pillar& pillar,float position);
	bool CollisionTest();
private:
	Player m_Player;

	uint32_t m_Score = 0;

	glm::vec3 m_PillarHSV{ 0.0f, 0.8f, 0.8f };

	glm::vec4 m_PlayerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};

	bool m_GameOver = false;
	std::vector<Pillar> m_Pillars;

	float m_DestroyPoint = -20.0f;
	float m_CreatePoint = 30.0f;

	Evil::Ref<Evil::Texture2D> m_PillarTexture;
};
