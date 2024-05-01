#pragma once

#include <glm/glm.hpp>

#include "TreeRoot/Events/Event.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tr {

	class OrthoCamera
	{
	public:
		OrthoCamera(float horizontal, float vertical);

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

		inline void SetProjectionMatrix(float horizontal, float vertical) { m_ProjectionMatrix = glm::ortho(-0.5f * horizontal, 0.5f * horizontal, -0.5f * vertical, 0.5f * vertical, -1.0f, 1.0f); }
		inline void SetViewMatrix(const glm::mat4 matrix) { m_ViewMatrix = matrix; }
		inline void SetProjectionViewMatrix(const glm::mat4 matrix) { m_ProjectionViewMatrix = matrix; }
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionViewMatrix;
	};

}