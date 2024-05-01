#include "trpch.h"
#include "Camera.h"

#include "Renderer.h"

namespace tr {

	OrthoCamera::OrthoCamera(float horizontal, float vertical)
	{
		m_ProjectionMatrix = glm::ortho(-0.5f * horizontal, 0.5f * horizontal, -0.5f * vertical, 0.5f * vertical, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}