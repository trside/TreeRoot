#pragma once

#include "TreeRoot/Layer.h"
#include "TreeRoot/Events/Event.h"

#include "TreeRoot/Events/ApplicationEvent.h"
#include "TreeRoot/Events/KeyEvent.h"
#include "TreeRoot/Events/MouseEvent.h"

namespace tr
{

	class TR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

		//bool OnWindowFocus(WindowFocusEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
	private:
		float m_Time = 0.0f;
	};

}


