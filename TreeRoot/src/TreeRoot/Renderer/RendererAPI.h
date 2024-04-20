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
		virtual ~RendererAPI() {}

		virtual void SetClearColor(const glm::vec4& clearColor) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}