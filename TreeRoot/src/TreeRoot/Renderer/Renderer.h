#pragma once

#include "RendererAPI.h"

namespace tr {

	class Renderer
	{
	public:
		static inline const RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
		static void SetAPI();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};

}