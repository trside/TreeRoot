#include <TreeRoot.h>

#include "Platform/OpenGL/OpenGLShader.h"	// Temporary

class ExampleLayer : public tr::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		std::string vertexSource = R"(
			#version 460 core
			
			layout(location = 0)in vec3 i_Position;
			layout(location = 1)in vec2 i_TexCoord;

			uniform mat4 u_PV;

			out vec2 v_TexCoord;
			
			void main()
			{
				gl_Position = u_PV * vec4(i_Position, 1.0);
				v_TexCoord = i_TexCoord;
			}
		)";
		std::string fragmentSource = R"(
			#version 460 core
			
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			out vec4 color;
			
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_Shader.reset(tr::Shader::Create(vertexSource, fragmentSource));

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

		m_Texture = tr::Texture::Create("assets/textures/iron_ore.png");
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetShaderParameter("u_Texture", 0);

		m_MainCamera.reset(new tr::OrthoCamera((float)tr::Application::Get().GetWindow().GetWidth(), (float)tr::Application::Get().GetWindow().GetHeight()));
	}

	virtual void OnUpdate(float deltaTime) override
	{
		m_FrameRate = 1.0f / deltaTime;

		tr::RenderCommand::SetClearColor({ 0.25, 0.25, 0.25, 1.0 });
		tr::RenderCommand::Clear();

		tr::Renderer::BeginScene(m_MainCamera);

		tr::Renderer::Submit(m_Shader, m_VertexArray);

		tr::Renderer::EndScene();

		//if (tr::Input::GetKey(TR_KEY_D))
		//	m_MainCamera_Position.x += m_MainCamera_MoveSpeed * deltaTime;
		//if (tr::Input::GetKey(TR_KEY_A))
		//	m_MainCamera_Position.x -= m_MainCamera_MoveSpeed * deltaTime;
		//if (tr::Input::GetKey(TR_KEY_W))
		//	m_MainCamera_Position.y += m_MainCamera_MoveSpeed * deltaTime;
		//if (tr::Input::GetKey(TR_KEY_S))
		//	m_MainCamera_Position.y -= m_MainCamera_MoveSpeed * deltaTime;

		if (tr::Input::GetKey(TR_KEY_Q))
			m_MainCamera_Rotation -= m_MainCamera_RotateSpeed * deltaTime;
		if (tr::Input::GetKey(TR_KEY_E))
			m_MainCamera_Rotation += m_MainCamera_RotateSpeed * deltaTime;

		if (tr::Input::GetKeyDown(TR_KEY_SPACE))
		{
			m_MainCamera_Position = { 0.0f, 0.0f };
			m_MainCamera_Rotation = 0.0f;
			m_MainCamera_Zoom = 1.0f;
		}
		/* CameraDragRotate Implementation================ */			// TODO: 实现鼠标拖拽旋转镜头，以鼠标点击位置为轴心
		if (tr::Input::GetMouseButtonDown(TR_MOUSE_BUTTON_1))
			m_LastCursorPosition = glm::vec2(tr::Input::GetMouseX(), tr::Input::GetMouseY());
		if (tr::Input::GetMouseButton(TR_MOUSE_BUTTON_1))
		{
			m_CurrentCursorPosition = { tr::Input::GetMouseX(), tr::Input::GetMouseY() };
			m_Different = m_CurrentCursorPosition - m_LastCursorPosition;
			//m_LastCursorPosition = m_CurrentCursorPosition;


		}
		/* =============================================== */

		/* CameraDragMove Implementation================== */
		if (tr::Input::GetMouseButtonDown(TR_MOUSE_BUTTON_2))
			m_CameraDragMove_LastCursorPosition = glm::vec2(tr::Input::GetMouseX(), tr::Input::GetMouseY());
		if (tr::Input::GetMouseButton(TR_MOUSE_BUTTON_2))
		{
			m_CameraDragMove_CurrentCursorPosition = { tr::Input::GetMouseX(), tr::Input::GetMouseY() };
			m_CameraDragMove_Different = m_CameraDragMove_CurrentCursorPosition - m_CameraDragMove_LastCursorPosition;
			m_CameraDragMove_LastCursorPosition = m_CameraDragMove_CurrentCursorPosition;

			m_CameraDragMove_Different =
				glm::vec4(m_CameraDragMove_Different, 0.0f, 1.0f) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_MainCamera_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / m_MainCamera_Zoom, 1.0f / m_MainCamera_Zoom, 1.0f));	// 将旋转和缩放变换应用到delta向量

			m_MainCamera_Position.x -= m_CameraDragMove_Different.x;
			m_MainCamera_Position.y += m_CameraDragMove_Different.y;
		}
		/* =============================================== */

		m_MainCamera->SetPosition(m_MainCamera_Position);
		m_MainCamera->SetRotation(m_MainCamera_Rotation);
		m_MainCamera->SetScale(m_MainCamera_Zoom);
	}

	virtual void OnEvent(tr::Event& e) override
	{
		//TR_TRACE("{0}", e);
		tr::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<tr::MouseScrolledEvent>(TR_BIND_EVENT(ExampleLayer::OnMouseScrolled));
		dispatcher.Dispatch<tr::WindowResizeEvent>(TR_BIND_EVENT(ExampleLayer::OnWindowResized));
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Debug Information");
		ImGui::Text("Frame Rate: %u", (unsigned int)m_FrameRate);
		ImGui::Text("m_LastCursorPosition: (%f, %f)", (float)m_CameraDragMove_LastCursorPosition.x, (float)m_CameraDragMove_LastCursorPosition.y);
		ImGui::Text("m_CurrentCursorPosition: (%f, %f)", (float)m_CameraDragMove_CurrentCursorPosition.x, (float)m_CameraDragMove_CurrentCursorPosition.y);
		ImGui::Text("m_Different: (%f, %f)", (float)m_CameraDragMove_Different.x, (float)m_CameraDragMove_Different.y);
		ImGui::Text("m_MainCamera_Position: (%f, %f)", (float)m_MainCamera_Position.x, (float)m_MainCamera_Position.y);
		ImGui::Text("m_ZoomRatios: %f", m_MainCamera_Zoom);
		ImGui::End();
	}

	bool OnMouseScrolled(tr::MouseScrolledEvent& e)
	{
		if (e.GetOffsetY() > 0)
			m_MainCamera_Zoom = m_ZoomRatios[m_ZoomRatios_Index + 1 > 22 ? m_ZoomRatios_Index : ++m_ZoomRatios_Index];
		else if (e.GetOffsetY() < 0)
			m_MainCamera_Zoom = m_ZoomRatios[m_ZoomRatios_Index - 1 < 0 ? m_ZoomRatios_Index : --m_ZoomRatios_Index];

		return false;
	}

	bool OnWindowResized(tr::WindowResizeEvent& e)
	{
		m_MainCamera->SetProjectionMatrix((float)tr::Application::Get().GetWindow().GetWidth(), (float)tr::Application::Get().GetWindow().GetHeight());

		return false;
	}
private:
	tr::Ref<tr::Shader> m_Shader;
	tr::Ref<tr::VertexArray> m_VertexArray;
	tr::Ref<tr::Texture> m_Texture;
	tr::Ref<tr::OrthoCamera> m_MainCamera;

	float m_MainCamera_MoveSpeed = 750.0f;
	float m_MainCamera_RotateSpeed = 90.0f;
	float m_ZoomRatios[23] = {
		1.0f / 64, 1.0f / 48, 1.0f / 32, 1.0f / 24, 1.0f / 16, 1.0f / 12, 1.0f / 8, 1.0f / 4, 1.0f / 3,
		1.0f / 2, 1, 2, 3, 4, 5, 6, 8, 12, 16, 24, 32, 48, 64
	};
	unsigned int m_ZoomRatios_Index = 10;

	glm::vec2 m_MainCamera_Position = { 0.0f, 0.0f };
	float m_MainCamera_Rotation = 0.0f;
	float m_MainCamera_Zoom = 1.0f;

	float m_FrameRate = 0.0f;

	/* CameraDragRotate Implementation================ */
	glm::vec2 m_LastCursorPosition = { 0.0f, 0.0f };
	glm::vec2 m_CurrentCursorPosition = { 0.0f, 0.0f };
	glm::vec2 m_Different = { 0.0f, 0.0f };
	/* =============================================== */


	/* CameraDragMove Implementation================== */
	glm::vec2 m_CameraDragMove_LastCursorPosition = { 0.0f, 0.0f };
	glm::vec2 m_CameraDragMove_CurrentCursorPosition = { 0.0f, 0.0f };
	glm::vec2 m_CameraDragMove_Different = { 0.0f, 0.0f };
	/* =============================================== */
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

