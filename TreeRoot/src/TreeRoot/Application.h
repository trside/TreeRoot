#pragma once

#include "Core.h"

namespace tr {

	class TR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	
	Application* CreateApplication();
}



