#include "trpch.h"

#include "Application.h"

namespace tr {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));		// 事件回调函数指针被从Window模块传到App中，再由App传输给其他模块（如Log）
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)		
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		TR_CORE_TRACE("{0}", e);
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}


