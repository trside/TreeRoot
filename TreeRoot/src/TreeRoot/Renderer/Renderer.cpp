#include "trpch.h"
#include "Renderer.h"

namespace tr {

	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;

	void Renderer::SetAPI(RendererAPI api)
	{
		s_RendererAPI = api;
	}

}
