#pragma once

#include <glm/glm.hpp>

#include "TreeRoot/Events/Event.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tr {

	class OrthoCamera
	{
	public:
		OrthoCamera(float width, float height);

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

		inline void SetProjectionMatrix(float width, float height)
		{
			m_ProjectionMatrix = glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height, -1.0f, 1.0f);
			RecalculateProjectionViewMatrix();
		}
		inline void SetViewMatrix(const glm::mat4 matrix)
		{
			m_ViewMatrix = matrix;
			RecalculateProjectionViewMatrix();
		}
	private:
		inline void RecalculateProjectionViewMatrix() { m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix; }

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionViewMatrix;
	};

}