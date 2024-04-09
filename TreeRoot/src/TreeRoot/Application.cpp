#include "trpch.h"

#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Log.h"

namespace tr {

	Application::Application()
	{
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizedEvent e(800, 600);
		TR_TRACE(e);
		while (true);
	}
}


