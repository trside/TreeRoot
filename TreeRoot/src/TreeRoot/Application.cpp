#include "trpch.h"

#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace tr {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}


