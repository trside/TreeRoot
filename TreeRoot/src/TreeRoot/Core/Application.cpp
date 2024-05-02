#include "trpch.h"

#include "Application.h"

#include "TreeRoot/Core/Input.h"

#include "TreeRoot/Renderer/Renderer.h"
#include "TreeRoot/Renderer/RenderCommand.h"

namespace tr {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		TR_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(TR_BIND_EVENT(Application::OnEvent));		// �¼��ص�����ָ�뱻��Windowģ�鴫��App�У�����App���������ģ�飨��Log��

		m_Time = Ref<Time>(Time::Create());

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(TR_BIND_EVENT(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(TR_BIND_EVENT(Application::OnWindowResized));

		//TR_CORE_TRACE("{0}", e);

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
			m_Time->UpdateDeltaTime();

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_Time->GetDeltaTime());
			}

			m_ImGuiLayer->OnImGuiFrameBegin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->OnImGuiFrameEnd();

			Input::OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e)		// TODO: ����������ڴ�Сʱglfw��ͣ��Ⱦ������ Tips: openGL˫�������
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;

			return false;
		}
		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
#if 0
		/* Temporary & Dangerous!!! */
		m_Time->UpdateDeltaTime();

		if (!m_Minimized)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(m_Time->GetDeltaTime());
		}

		m_ImGuiLayer->OnImGuiFrameBegin();

		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();

		m_ImGuiLayer->OnImGuiFrameEnd();

		Input::OnUpdate();

		m_Window->OnUpdate();
#endif
		return false;
	}
}

