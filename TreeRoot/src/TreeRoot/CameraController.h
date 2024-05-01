#pragma once

#include "TreeRoot/Renderer/Camera.h"

#include "TreeRoot/Events/ApplicationEvent.h"
#include "TreeRoot/Events/MouseEvent.h"

namespace tr {

	class OrthoCameraController
	{
	public:
		OrthoCameraController(float horizontal, float vertical, bool rotate = false);

		inline const glm::vec2& GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }
		inline float GetScale() const { return m_ZoomRatio; }

		inline void SetPosition(const glm::vec2& position) { m_Position = position; RecalculateViewMatrix(); }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		inline void SetScale(float scale) { m_ZoomRatio = std::max(0.0f, scale); RecalculateViewMatrix(); }

		inline const OrthoCamera& GetCamera() const { return m_Camera; }
		inline OrthoCamera& GetCamera() { return m_Camera; }

		void OnUpdate(float deltaTime);

		void OnEvent(Event& e);

		void OnImGuiRender();
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		void RecalculateViewMatrix();

		bool m_EnableRotate;

		glm::vec2 m_Position;
		float m_Rotation;
		float m_ZoomRatio;

		OrthoCamera m_Camera;

		glm::vec2 m_LastCursorPosition, m_CurrentCursorPosition, m_Different;

		float m_RotateSpeed = 90.0f;

		float m_ZoomRatios[23] = {
			1.0f / 64, 1.0f / 48, 1.0f / 32, 1.0f / 24, 1.0f / 16, 1.0f / 12, 1.0f / 8, 1.0f / 4, 1.0f / 3,
			1.0f / 2, 1, 2, 3, 4, 5, 6, 8, 12, 16, 24, 32, 48, 64
		};
		int m_ZoomRatiosIndex = 10;
	};

}