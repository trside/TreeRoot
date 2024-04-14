#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "TreeRoot/LayerStack.h"
#include "TreeRoot/Imgui/ImGuiLayer.h"

namespace tr {

	class TR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() const { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		
		bool m_Running = true;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance;
	};
	
	Application* CreateApplication();
}


