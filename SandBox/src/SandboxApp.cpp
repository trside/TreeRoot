#include <TreeRoot.h>

class ExampleLayer : public tr::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		  m_MainCameraController((float)tr::Application::Get().GetWindow().GetWidth(), (float)tr::Application::Get().GetWindow().GetHeight())

	{
		m_Shader = tr::Shader::Create("assets/shaders/BasicShader.glsl");

		m_ShaderLibrary.Add(m_Shader);

		m_VertexArray.reset(tr::VertexArray::Create());

		tr::BufferLayout layout = {
			{ tr::ShaderDataType::Float2, "i_Position" },
			{ tr::ShaderDataType::Float2, "i_TexCoord" },
		};

		tr::Ref<tr::VertexBuffer> vertexBuffer;
		tr::Ref<tr::IndexBuffer> indexBuffer;

		float vertices[4 * (2 + 2)] = {
			   0.0,    0.0,  0.0,  0.0,
			 100.0,    0.0,  2.0,  0.0,
			 100.0,  100.0,  2.0,  2.0,
			   0.0,  100.0,  0.0,  2.0
		};

		vertexBuffer.reset(tr::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[2 * 3] = { 0, 1, 2, 2, 3, 0 };

		indexBuffer.reset(tr::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		auto basicShader = m_ShaderLibrary.Get("BasicShader");

		basicShader->Bind();
		basicShader->SetShaderParameter("u_Texture", 0);

		m_Texture = tr::Texture::Create("assets/textures/iron_ore.png");

		m_AlphaTexture = tr::Texture::Create("assets/textures/glass_purple.png");

	}

	virtual void OnUpdate(float deltaTime) override
	{
		m_FrameRate = 1.0f / deltaTime;

		TR_TRACE("m_FrameRate: {0}", m_FrameRate);

		m_MainCameraController.OnUpdate(deltaTime);

		tr::RenderCommand::SetClearColor({ 0.25, 0.25, 0.25, 1.0 });
		tr::RenderCommand::Clear();

		tr::Renderer::BeginScene(m_MainCameraController.GetCamera());

		auto basicShader = m_ShaderLibrary.Get("BasicShader");
		m_Texture->Bind();
		tr::Renderer::Submit(basicShader, m_VertexArray);
		m_AlphaTexture->Bind();
		tr::Renderer::Submit(basicShader, m_VertexArray);

		tr::Renderer::EndScene();
	}

	virtual void OnEvent(tr::Event& e) override
	{
		m_MainCameraController.OnEvent(e);
	}

	virtual void OnImGuiRender() override
	{
		m_MainCameraController.OnImGuiRender();

		ImGui::Begin("AppInfo");
		ImGui::Text("m_FrameRate: %f", m_FrameRate);
		ImGui::End();
	}
private:
	tr::ShaderLibrary m_ShaderLibrary;
	tr::Ref<tr::Shader> m_Shader;
	tr::Ref<tr::VertexArray> m_VertexArray;
	tr::Ref<tr::Texture> m_Texture;
	tr::Ref<tr::Texture> m_AlphaTexture;
	tr::OrthoCameraController m_MainCameraController;

	float m_FrameRate = 0.0f;
};

class Sandbox : public tr::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

tr::Application* tr::CreateApplication()
{
	return new Sandbox;
}

