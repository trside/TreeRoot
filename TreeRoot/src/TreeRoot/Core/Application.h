#pragma once

#include "TreeRoot/Core/Core.h"
#include "TreeRoot/Core/Window.h"

#include "TreeRoot/Events/Event.h"
#include "TreeRoot/Events/ApplicationEvent.h"

#include "TreeRoot/Core/LayerStack.h"
#include "TreeRoot/ImGui/ImGuiLayer.h"

#include "TreeRoot/Core/Time.h"

namespace tr {

	class Application
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
		bool OnWindowResized(WindowResizeEvent& e);

		Scope<Window> m_Window;

		Ref<Time> m_Time;
		
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance;
	};
	
	Application* CreateApplication();
}


