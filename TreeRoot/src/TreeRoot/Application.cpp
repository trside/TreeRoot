#include "trpch.h"

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>		// Temporary

#include "TreeRoot/Input.h"

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

		glGenBuffers(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		float vertices[3 * 3] = {
			-0.5, -0.5,  0.0,
			 0.5, -0.5,  0.0,
			 0.0,  0.5,  0.0
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		unsigned int indices[3] = {
			0, 1, 2
		};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
			glClear(GL_COLOR_BUFFER_BIT);	// Temporary

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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


