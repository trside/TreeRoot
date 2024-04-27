#include "trpch.h"
#include "Shader.h"

#include "TreeRoot/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace tr {
	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(filePath);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
    }

}
