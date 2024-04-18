#include "trpch.h"

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace tr {

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window) {}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TR_CORE_ASSERT(status, "Failed to initialize Glad!");

		TR_CORE_INFO("OpenGL Info: ");
		TR_CORE_INFO("    Vendor:   {0}", (const char*)glGetString(GL_VENDOR));
		TR_CORE_INFO("    Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		TR_CORE_INFO("    Version:  {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

}