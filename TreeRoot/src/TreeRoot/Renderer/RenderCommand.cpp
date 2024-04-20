#include "trpch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace tr {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}