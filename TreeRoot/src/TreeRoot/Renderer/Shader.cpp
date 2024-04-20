#include "trpch.h"
#include "Shader.h"

#include "TreeRoot/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace tr {

    Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSource, fragmentSource);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
    }

}
