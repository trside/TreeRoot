#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "TreeRoot/LayerStack.h"
#include "TreeRoot/ImGui/ImGuiLayer.h"

#include "TreeRoot/Renderer/Shader.h"
#include "TreeRoot/Renderer/VertexArray.h"
#include "TreeRoot/Renderer/Buffers.h"

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

		std::unique_ptr<Window> m_Window;
		
		bool m_Running = true;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance;

		/* Temporary */
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_VertexArray;
	};
	
	Application* CreateApplication();
}


