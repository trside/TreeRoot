#include "trpch.h"
#include "Camera.h"

#include "Renderer.h"

namespace tr {
	OrthoCamera::OrthoCamera(glm::vec2 matrix)
		: m_ViewMatrix(1.0f),
		  m_Position(glm::vec2(0.0f, 0.0f)), m_Rotation(0.0f), m_Scale(1.0f)
	{
		m_ProjectionMatrix = glm::ortho(-0.5f * matrix.x, 0.5f * matrix.x, -0.5f * matrix.y, 0.5f * matrix.y, 0.0f, 1.0f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	OrthoCamera::OrthoCamera(float width, float height)
		: m_ViewMatrix(1.0f),
		  m_Position(glm::vec2(0.0f, 0.0f)), m_Rotation(0.0f), m_Scale(1.0f)
	{
		m_ProjectionMatrix = glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height, 0.0f, 1.0f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthoCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix =
			glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 1.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, m_Scale, 1.0f));
		m_ViewMatrix = glm::inverse(m_ViewMatrix);

		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}