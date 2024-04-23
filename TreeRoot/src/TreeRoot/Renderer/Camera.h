#pragma once

#include <glm/glm.hpp>

#include "TreeRoot/Events/Event.h"

namespace tr {

	class OrthoCamera
	{
	public:
		OrthoCamera(float width, float height);

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		inline const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

		inline const glm::vec2& GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }
		inline const float GetScale() const { return m_Scale; }

		inline void SetPosition(const glm::vec2& position) { m_Position = position; RecalculateViewMatrix(); }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		inline void SetScale(float scale) { scale = 1 / scale; m_Scale = scale < 0.0f ? 0.0f : scale; RecalculateViewMatrix(); }

		void RecalculateViewMatrix();	// Recalculate m_ViewMatrix
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionViewMatrix;

		glm::vec2 m_Position;
		float m_Rotation;
		float m_Scale;
	};

}