#pragma once

#include "TreeRoot/Window.h"

#include "TreeRoot/Renderer/RendererContext.h"

#include <GLFW/glfw3.h>

namespace tr {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual inline unsigned int GetWidth() const override { return m_Data.Width; }
		virtual inline unsigned int GetHeight() const override { return m_Data.Height; }
		virtual inline void* GetNativeWindow() const { return m_Window; }

		virtual inline void SetEventCallback(const EventCallbackFun& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFun EventCallback;
		};
		WindowData m_Data;
		RendererContext* m_Context;
	};
}

