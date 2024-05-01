#pragma once

#include "RendererAPI.h"

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

namespace tr {

	class Renderer
	{
	public:
		static void Init();

		static inline const RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }
		static void SetAPI();

		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
	private:
		struct SceneData
		{
			glm::mat4 ProjectionViewMatrix;
		};
		static SceneData* s_SceneData;
	};

}