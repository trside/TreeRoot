#pragma once

#include "RendererAPI.h"

#include "Shader.h"
#include "Camera.h"

namespace tr {

	class Renderer
	{
	public:
		static inline const RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
		static void SetAPI();

		static void BeginScene(const std::shared_ptr<Camera>& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
	private:
	struct SceneData
	{
		glm::mat4 ProjectionViewMatrix;
	};
		static SceneData* s_SceneData;
	};

}