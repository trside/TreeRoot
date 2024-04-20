#include "trpch.h"
#include "Buffers.h"

#include "Platform/OpenGL/OpenGLBuffers.h"
#include "TreeRoot/Renderer/Renderer.h"

namespace tr {

	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
	}

}