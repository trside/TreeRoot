#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace tr {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& clearColor) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}