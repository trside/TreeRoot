#include "Sandbox2DLayer.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("SandBox2D"),
	  m_MainCameraController((float)tr::Application::Get().GetWindow().GetWidth(), (float)tr::Application::Get().GetWindow().GetHeight())
{
	m_FlatColorQuadColor = { 0.3f, 0.7f, 0.6f, 1.0f };
	m_FlatColorQuadPosition = { 0.0f, 0.0f, 0.0f };
	m_FlatColorQuadScale = { 1.0f, 1.0f };

	m_TextureQuadColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_TextureQuadPosition = { 0.0f, 0.0f, 0.0f };
	m_TextureQuadScale = { 1.0f, 1.0f };

	m_Texture = tr::Texture::Create("assets/textures/iron_ore.png");
}

void Sandbox2DLayer::OnAttach()
{
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(float deltaTime)
{
	m_FrameRate = 1.0f / deltaTime;

	//TR_TRACE("m_FrameRate: {0}", m_FrameRate);

	m_MainCameraController.OnUpdate(deltaTime);

	tr::RenderCommand::SetClearColor({ 0.25, 0.25, 0.25, 1.0 });
	tr::RenderCommand::Clear();

	tr::Renderer2D::BeginScene(m_MainCameraController.GetCamera());

	tr::Renderer2D::DrawQuad(m_FlatColorQuadPosition, m_FlatColorQuadScale, m_FlatColorQuadColor);
	tr::Renderer2D::DrawQuad(m_TextureQuadPosition, m_TextureQuadScale, m_Texture, m_TextureQuadColor);

	tr::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnEvent(tr::Event& e)
{
	m_MainCameraController.OnEvent(e);
}

void Sandbox2DLayer::OnImGuiRender()
{
	m_MainCameraController.OnImGuiRender();

	ImGui::Begin("AppInfo");
	ImGui::Text("m_FrameRate: %f", m_FrameRate);
	ImGui::End();

	ImGui::Begin("FlatColorQuad");
	ImGui::DragFloat3("Position", glm::value_ptr(m_FlatColorQuadPosition));
	ImGui::DragFloat2("Scale", glm::value_ptr(m_FlatColorQuadScale));
	ImGui::ColorEdit4("Color", glm::value_ptr(m_FlatColorQuadColor));
	ImGui::End();

	ImGui::Begin("TextureQuad");
	ImGui::DragFloat3("Position", glm::value_ptr(m_TextureQuadPosition));
	ImGui::DragFloat2("Scale", glm::value_ptr(m_TextureQuadScale));
	ImGui::ColorEdit4("Color", glm::value_ptr(m_TextureQuadColor));
	ImGui::End();
}
