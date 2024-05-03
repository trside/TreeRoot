#pragma once

#include <TreeRoot.h>

class Sandbox2DLayer : public tr::Layer
{
public:
	Sandbox2DLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(tr::Event& e) override;
	virtual void OnImGuiRender() override;
private:
	tr::OrthoCameraController m_MainCameraController;

	glm::vec3 m_FlatColorQuadPosition;
	glm::vec2 m_FlatColorQuadScale;
	glm::vec4 m_FlatColorQuadColor;

	glm::vec3 m_TextureQuadPosition;
	glm::vec2 m_TextureQuadScale;
	glm::vec4 m_TextureQuadColor;

	tr::Ref<tr::Texture> m_Texture;

	float m_FrameRate = 0.0f;
};