#pragma once

#include <glm/glm.hpp>

#include "TreeRoot/Events/Event.h"

namespace tr {

	class Camera
	{
	public:
		Camera(float width, float height);
		~Camera();

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		inline const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

		void SetProjectionMatrix(float width, float height);

		void Translate(const glm::vec3& position) { m_Position = position; }
		void Rotate(float rotation) { m_Rotation = rotation; }
		void Scaling(glm::vec2 scaling) { m_Scaling = scaling; }

		void OnUpdate();	// Calculate m_ProjectionViewMatrix
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionViewMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
		glm::vec2 m_Scaling;
	};

}