#include "trpch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "TreeRoot/Renderer/Renderer.h"

namespace tr {

    VertexArray* VertexArray::Create()
    {
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::None:		TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

}
