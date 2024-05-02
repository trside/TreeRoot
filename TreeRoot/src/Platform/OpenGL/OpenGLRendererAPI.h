#pragma once

#include "Treeroot/Renderer/RendererAPI.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace tr {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual ~OpenGLRendererAPI() {}

		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& clearColor) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

		virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
	};

}