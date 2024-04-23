#include "trpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace tr {

	Ref<Texture> Texture::Create(const std::string& path)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture>(path);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
	}

}