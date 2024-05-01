#include "trpch.h"
#include "CameraController.h"

#include "TreeRoot/Input.h"

#include "TreeRoot/Core.h"

#include "TreeRoot/Application.h"

#include "imgui/imgui.h"

namespace tr {

	OrthoCameraController::OrthoCameraController(float horizontal, float vertical, bool rotate)
		: m_EnableRotate(rotate), m_Camera(horizontal, vertical), m_Position({ 0.0f, 0.0f }), m_Rotation(0.0f), m_ZoomRatio(1.0f)
	{
	}

	void OrthoCameraController::OnUpdate(float deltaTime)
	{
		if (m_EnableRotate)
		{
			if (Input::GetKey(TR_KEY_Q))
				m_Rotation -= m_RotateSpeed * deltaTime;
			if (Input::GetKey(TR_KEY_E))
				m_Rotation += m_RotateSpeed * deltaTime;
		}

		if (Input::GetKeyDown(TR_KEY_SPACE))
		{
			m_Position = { 0.0f, 0.0f };
			m_Rotation = 0.0f;
			m_ZoomRatio = 1.0f;

			m_ZoomRatiosIndex = 10;
		}

		if (Input::GetMouseButtonDown(TR_MOUSE_BUTTON_2))
			m_LastCursorPosition = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
		if (Input::GetMouseButton(TR_MOUSE_BUTTON_2))
		{
			m_CurrentCursorPosition = { Input::GetMouseX(), Input::GetMouseY() };
			m_Different = m_CurrentCursorPosition - m_LastCursorPosition;
			m_LastCursorPosition = m_CurrentCursorPosition;

			m_Different =
				glm::vec4(m_Different, 0.0f, 1.0f) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(m_ZoomRatio, m_ZoomRatio, 1.0f));	// 将旋转和缩放变换应用到delta向量

			m_Position.x -= m_Different.x;
			m_Position.y += m_Different.y;
			//m_Position += glm::vec2(-m_Different.x, m_Different.y);
		}
		RecalculateViewMatrix();
	}

	void OrthoCameraController::RecalculateViewMatrix()
	{
		m_Camera.SetViewMatrix(
			glm::inverse(
				glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 1.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(m_ZoomRatio, m_ZoomRatio, 1.0f))
			)
		);

		m_Camera.SetProjectionViewMatrix(m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix());
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(TR_BIND_EVENT(OrthoCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(TR_BIND_EVENT(OrthoCameraController::OnWindowResized));
	}

	void OrthoCameraController::OnImGuiRender()
	{
		ImGui::Begin("Debug Information");
		ImGui::Text("m_CurrentCursorPosition: (%f, %f)", (float)m_CurrentCursorPosition.x, (float)m_CurrentCursorPosition.y);
		ImGui::Text("m_Position: (%f, %f)", (float)m_Position.x, (float)m_Position.y);
		ImGui::Text("m_ZoomRatio: %f", m_ZoomRatio);
		ImGui::End();

		ImGui::Begin("Main Camera");

		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputFloat("Position.x", &m_Position.x);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputFloat("Position.y", &m_Position.y);

		ImGui::BeginDisabled(!m_EnableRotate);
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputFloat("Rotation", &m_Rotation);
		ImGui::EndDisabled();
		ImGui::SameLine();
		ImGui::Checkbox("Enable Rotation", &m_EnableRotate);

		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputFloat("Zoom", &m_ZoomRatio);

		ImGui::End();
	}

	bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_Position.x += m_ZoomRatio * (Input::GetMouseX() - 0.5f * (float)Application::Get().GetWindow().GetWidth());
		m_Position.y -= m_ZoomRatio * (Input::GetMouseY() - 0.5f * (float)Application::Get().GetWindow().GetHeight()) ;

		if (e.GetOffsetY() > 0)
			m_ZoomRatio = m_ZoomRatios[(m_ZoomRatiosIndex - 1 < 0) ? m_ZoomRatiosIndex : --m_ZoomRatiosIndex];
		else if (e.GetOffsetY() < 0)
			m_ZoomRatio = m_ZoomRatios[(m_ZoomRatiosIndex + 1 > 22) ? m_ZoomRatiosIndex : ++m_ZoomRatiosIndex];

		m_Position.x -= m_ZoomRatio * (Input::GetMouseX() - 0.5f * (float)Application::Get().GetWindow().GetWidth());
		m_Position.y += m_ZoomRatio * (Input::GetMouseY() - 0.5f * (float)Application::Get().GetWindow().GetHeight());

		return false;
	}

	bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Camera.SetProjectionMatrix((float)Application::Get().GetWindow().GetWidth(), (float)Application::Get().GetWindow().GetHeight());

		return false;
	}

}