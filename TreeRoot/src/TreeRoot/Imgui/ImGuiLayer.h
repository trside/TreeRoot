#pragma once

#include "TreeRoot/Layer.h"
#include "TreeRoot/Events/Event.h"

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
	private:
		float m_Time = 0.0f;
	};

}


