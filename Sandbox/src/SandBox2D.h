#pragma once

#include "Evil.h"

#include "ParticleSystem.h"

class SandBox2D: public Evil::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Evil::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Evil::Event& e) override;
private:
	Evil::OrthographicCameraController m_CameraController;

	Evil::Ref<Evil::Texture2D> m_CheckerboardTexture;
	Evil::Ref<Evil::Texture2D> m_SpriteSheet;
	Evil::Ref<Evil::SubTexture2D> m_TextureTree;
	Evil::Ref<Evil::Texture2D> m_CLogo;



	glm::vec4 m_SquareColor;
};