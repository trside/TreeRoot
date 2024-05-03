#include "trpch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "TreeRoot/Renderer/Renderer.h"

namespace tr {

	Ref<VertexArray> VertexArray::Create()
    {
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

        return nullptr;
    }

}
