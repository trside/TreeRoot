#pragma once

#include <TreeRoot.h>

class ExampleLayer : public tr::Layer
{
public:
	ExampleLayer();

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(tr::Event& e) override;
	virtual void OnImGuiRender() override;
private:
	tr::ShaderLibrary m_ShaderLibrary;
	tr::Ref<tr::Shader> m_Shader;
	tr::Ref<tr::VertexArray> m_VertexArray;
	tr::Ref<tr::Texture> m_Texture;
	tr::Ref<tr::Texture> m_AlphaTexture;
	tr::OrthoCameraController m_MainCameraController;

	float m_FrameRate = 0.0f;
};