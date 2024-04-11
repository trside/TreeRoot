#include "trpch.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace tr {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		TR_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));		// �¼��ص�����ָ�뱻��Windowģ�鴫��App�У�����App���������ģ�飨��Log��
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		/* Temporary ================================*/
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		/*===========================================*/

		TR_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)		// �¼����ݷ����ڲ�ջ��Ϊ�Զ�����
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
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	/* Temporary */
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}


