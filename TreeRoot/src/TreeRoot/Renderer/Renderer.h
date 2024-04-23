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

		static void BeginScene(const Ref<Camera>& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);
	private:
		struct SceneData
		{
			glm::mat4 ProjectionViewMatrix;
		};
		static SceneData* s_SceneData;
	};

}