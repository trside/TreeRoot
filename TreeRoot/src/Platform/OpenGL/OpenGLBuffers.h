#pragma once

#include "TreeRoot/Renderer/Buffers.h"

#include <Glad/glad.h>

namespace tr {

	/* Vertex Buffer */
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual inline const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	/* Index Buffer */
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* vertices, unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline unsigned int GetCount() const { return m_Count; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};

}