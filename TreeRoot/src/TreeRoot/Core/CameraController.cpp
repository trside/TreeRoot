#include "trpch.h"
#include "CameraController.h"

#include "TreeRoot/Core/Input.h"

#include "TreeRoot/Core/Core.h"

#include "TreeRoot/Core/Application.h"

#include "imgui/imgui.h"

namespace tr {

	OrthoCameraController::OrthoCameraController(float width, float height, bool rotate)		// 镜头囊括的世界的长宽（镜头控制器拥有）， 窗口长宽（事件系统传递），二者的长宽比相同，需要的是二者的比率，才能将鼠标在窗口中的操作映射到镜头上
		: m_EnableRotate(rotate), m_Camera(width, height), m_Position({ 0.0f, 0.0f }), m_Rotation(0.0f), m_Scale(1.0f),
		  m_AspectRatio(width / height), m_WorldWidth(width), m_WorldHeight(height)
	{
		l_LastWindowWidth = (float)Application::Get().GetWindow().GetWidth();
		l_LastWindowHeight = (float)Application::Get().GetWindow().GetHeight();
	}

	void OrthoCameraController::OnUpdate(float deltaTime)
	{
		if (Input::GetKeyDown(TR_KEY_K))
			TR_TRACE("Jump!");

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
			m_Scale = 1.0f;

			l_ScalesIndex = 10;
		}

		float width = (float)Application::Get().GetWindow().GetWidth();
		float height = (float)Application::Get().GetWindow().GetHeight();

		float mouseX = m_WorldWidth / width * Input::GetMouseX();
		float mouseY = m_WorldHeight / height * Input::GetMouseY();

		if (Input::GetMouseButtonDown(TR_MOUSE_BUTTON_2))
			l_LastCursorPosition = { mouseX, mouseY };
		if (Input::GetMouseButton(TR_MOUSE_BUTTON_2))
		{
			l_CurrentCursorPosition = { mouseX, mouseY };
			l_Different = l_CurrentCursorPosition - l_LastCursorPosition;
			l_LastCursorPosition = l_CurrentCursorPosition;

			l_Different =
				glm::vec4(l_Different, 0.0f, 1.0f) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, m_Scale, 1.0f));	// 将旋转和缩放变换应用到delta向量

			m_Position.x -= l_Different.x;
			m_Position.y += l_Different.y;
		}

		m_Camera.SetViewMatrix(
			glm::inverse(
				glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 1.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, m_Scale, 1.0f))
			)
		);
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
		ImGui::Text("m_CurrentCursorPosition: (%f, %f)", (float)l_CurrentCursorPosition.x, (float)l_CurrentCursorPosition.y);
		ImGui::Text("m_Position: (%f, %f)", (float)m_Position.x, (float)m_Position.y);
		ImGui::Text("m_AspectRatio: %f", m_AspectRatio);
		ImGui::Text("m_WorldWidth: %f", m_WorldWidth);
		ImGui::Text("m_WorldHeight: %f", m_WorldHeight);
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
		ImGui::InputFloat("Zoom", &m_Scale);

		ImGui::End();
	}

	bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		float width = (float)Application::Get().GetWindow().GetWidth();
		float height = (float)Application::Get().GetWindow().GetHeight();

		float mouseX = m_WorldWidth / width * Input::GetMouseX();
		float mouseY = m_WorldHeight / height * Input::GetMouseY();

		m_Position.x += m_Scale * (mouseX - 0.5f * m_WorldWidth);
		m_Position.y -= m_Scale * (mouseY - 0.5f * m_WorldHeight);

		if (e.GetOffsetY() > 0)
			m_Scale = l_Scales[(l_ScalesIndex - 1 < 0) ? l_ScalesIndex : --l_ScalesIndex];
		else if (e.GetOffsetY() < 0)
			m_Scale = l_Scales[(l_ScalesIndex + 1 > 22) ? l_ScalesIndex : ++l_ScalesIndex];

		m_Position.x -= m_Scale * (mouseX - 0.5f * m_WorldWidth);
		m_Position.y += m_Scale * (mouseY - 0.5f * m_WorldHeight);

		return false;
	}

	bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		float windowWidth = (float)Application::Get().GetWindow().GetWidth();
		float windowHeight = (float)Application::Get().GetWindow().GetHeight();

		m_AspectRatio = windowWidth / windowHeight;

		/* 水平拉伸窗口 */
		if (l_LastWindowHeight == windowHeight)
		{
			if (windowWidth > windowHeight)
			{
				m_WorldHeight = m_WorldWidth / m_AspectRatio;
			}
			else if (windowWidth < windowHeight)
			{
				m_WorldWidth *= windowWidth / l_LastWindowWidth;
			}
		}
		/* 竖直拉伸窗口 */
		else if (l_LastWindowWidth == windowWidth)
		{
			if (windowHeight > windowWidth)
			{
				m_WorldWidth = m_WorldHeight * m_AspectRatio;
			}
			if (windowHeight < windowWidth)
			{
				m_WorldHeight *= windowHeight / l_LastWindowHeight;
			}
		}

		else if (l_LastWindowHeight != windowHeight && l_LastWindowWidth != windowWidth)
		{
			if (windowWidth > windowHeight)
			{
				m_WorldHeight = m_WorldWidth / m_AspectRatio;
			}
			if (windowHeight > windowWidth)
			{
				m_WorldWidth = m_WorldHeight * m_AspectRatio;
			}
		}

		m_Camera.SetProjectionMatrix(m_WorldWidth, m_WorldHeight);

		l_LastWindowWidth = windowWidth;
		l_LastWindowHeight = windowHeight;

		return false;
	}

}