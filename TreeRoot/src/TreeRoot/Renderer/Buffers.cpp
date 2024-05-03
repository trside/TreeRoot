#include "trpch.h"
#include "Buffers.h"

#include "Platform/OpenGL/OpenGLBuffers.h"
#include "TreeRoot/Renderer/Renderer.h"

namespace tr {

	Ref<VertexBuffer> VertexBuffer::Create(const float* vertices, unsigned int size)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(const unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
	}

}