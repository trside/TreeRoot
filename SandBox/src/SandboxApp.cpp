#include <TreeRoot.h>

class ExampleLayer : public tr::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		std::string vertexSource = R"(
			#version 460 core
			
			layout(location = 0)in vec3 i_Position;
			layout(location = 1)in vec4 i_Color;

			uniform mat4 u_PV;

			out vec4 v_Color;
			
			void main()
			{
				gl_Position = u_PV * vec4(i_Position, 1.0);
				v_Color = i_Color;
			}
		)";
		std::string fragmentSource = R"(
			#version 460 core
			
			in vec4 v_Color;
			out vec4 color;
			
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(tr::Shader::Create(vertexSource, fragmentSource));

		m_VertexArray.reset(tr::VertexArray::Create());

		tr::BufferLayout layout = {
			{ tr::ShaderDataType::Float3, "i_Position" },
			{ tr::ShaderDataType::Float4, "i_Color" },
		};

		std::shared_ptr<tr::VertexBuffer> vertexBuffer;
		std::shared_ptr<tr::IndexBuffer> indexBuffer;

		float vertices[3 * (4 + 3)] = {
			   0.0,    0.0,  0.0,  0.0,  1.0,  0.0,  1.0,
			 100.0,    0.0,  0.0,  0.0,  1.0,  0.0,  1.0,
			  50.0,  100.0,  0.0,  0.0,  1.0,  0.0,  1.0
		};

		vertexBuffer.reset(tr::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		indexBuffer.reset(tr::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_MainCamera.reset(new tr::Camera((float)tr::Application::Get().GetWindow().GetWidth(), (float)tr::Application::Get().GetWindow().GetHeight()));
	}

	virtual void OnUpdate(float deltaTime) override
	{
		tr::RenderCommand::SetClearColor({ 0.25, 0.25, 0.25, 1.0 });
		tr::RenderCommand::Clear();

		tr::Renderer::BeginScene(m_MainCamera);

		m_Shader->Bind();
		m_VertexArray->Bind();
		tr::Renderer::Submit(m_Shader, m_VertexArray);

		tr::Renderer::EndScene();

		if (tr::Input::GetMouseButtonDown(TR_MOUSE_BUTTON_1))
			TR_CORE_INFO("down!!");
		if (tr::Input::GetMouseButton(TR_MOUSE_BUTTON_1))
			TR_CORE_INFO("hold!!");
		if (tr::Input::GetMouseButtonUp(TR_MOUSE_BUTTON_1))
			TR_CORE_INFO("up!!");

		m_MainCamera->OnUpdate();

	}

	virtual void OnEvent(tr::Event& e) override
	{
		//TR_TRACE("{0}", e);
	}

	virtual void OnImGuiRender() override
	{
	}
private:
	std::shared_ptr<tr::Shader> m_Shader;
	std::shared_ptr<tr::VertexArray> m_VertexArray;
	std::shared_ptr<tr::Camera> m_MainCamera;
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

