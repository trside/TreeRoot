#include "trpch.h"

#include "Application.h"

#include "TreeRoot/Input.h"

/* Temporary */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TreeRoot/Renderer/Renderer.h"
#include "TreeRoot/Renderer/RenderCommand.h"

namespace tr {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		TR_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(TR_BIND_EVENT(Application::OnEvent));		// 事件回调函数指针被从Window模块传到App中，再由App传输给其他模块（如Log）

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		std::string vertexSource = R"(
			#version 460 core
			
			layout(location = 0)in vec3 i_Position;
			layout(location = 1)in vec4 i_Color;
			out vec4 v_Color;
			
			void main()
			{
				gl_Position = vec4(i_Position, 1.0);
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

		m_Shader.reset(Shader::Create(vertexSource, fragmentSource));

		m_VertexArray.reset(VertexArray::Create());

		BufferLayout layout = {
			{ ShaderDataType::Float3, "i_Position" },
			{ ShaderDataType::Float4, "i_Color" }
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;

		float vertices[3 * (4 + 3)] = {
			-0.5, -0.5,  0.0,  1.0,  0.5,  1.0,  1.0,
			 0.5, -0.5,  0.0,  1.0,  0.5,  1.0,  1.0,
			 0.0,  0.5,  0.0,  1.0,  0.5,  1.0,  1.0
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		
		unsigned int indices[3] = {
			0, 1, 2
		};

		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(TR_BIND_EVENT(Application::OnWindowClose));

		// TR_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)		// 事件传递方向在层栈中为自顶向下
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
		TR_CORE_INFO("Layer: {0} pushed", layer->GetName());
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
		TR_CORE_INFO("Overlay: {0} pushed", overlay->GetName());
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			//glClear(GL_COLOR_BUFFER_BIT);	// Temporary
			RenderCommand::SetClearColor({ 1.0, 1.0, 0.0, 1.0 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			m_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->OnImGuiFrameBegin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->OnImGuiFrameEnd();

			m_Window->OnUpdate();

			// Test input polling
			static bool IsMouseButton1Holding;
			if (!Input::IsMouseButtonPressed(TR_MOUSE_BUTTON_1))
			{
				IsMouseButton1Holding = false;
			}
			if (Input::IsKeyPressed(TR_KEY_E) && Input::IsMouseButtonPressed(TR_MOUSE_BUTTON_1) && !IsMouseButton1Holding)
			{
				TR_CORE_TRACE("Clicked at ({0}, {1}).", Input::GetMouseX(), Input::GetMouseY());
				IsMouseButton1Holding = true;
			}
		}
	}

	/* Temporary */
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}


