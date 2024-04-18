#pragma once

#include "TreeRoot/Renderer/RendererContext.h"

struct GLFWwindow;

namespace tr {

	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};

}


