#pragma once

#include "TreeRoot/Renderer/Buffers.h"

namespace tr {

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<VertexArray> Create();

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual inline const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
	};

}