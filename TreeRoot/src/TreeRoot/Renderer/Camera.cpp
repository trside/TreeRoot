#include "trpch.h"
#include "Camera.h"

#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tr {

	Camera::Camera(float width, float height)
		: m_ProjectionMatrix(1.0f), m_ViewMatrix(1.0f),
		  m_Position(glm::vec3(0.0f, 0.0f, 0.0f)), m_Rotation(0.0f), m_Scaling(glm::vec2(1.0f, 1.0f))
	{
		m_ProjectionMatrix = glm::ortho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	}

	Camera::~Camera()
	{
	}

	void Camera::SetProjectionMatrix(float width, float height)
	{
		m_ProjectionMatrix = glm::ortho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	}

	void Camera::OnUpdate()
	{
		m_ViewMatrix =
			glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f),
			glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f),
			glm::vec3(m_Scaling.x, m_Scaling.y, 1.0f));

		m_ViewMatrix = glm::inverse(m_ViewMatrix);

		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}