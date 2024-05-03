#pragma once

#include "TreeRoot/Core/CameraController.h"
#include "TreeRoot/Renderer/Texture.h"

namespace tr {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);

		static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	};

}
