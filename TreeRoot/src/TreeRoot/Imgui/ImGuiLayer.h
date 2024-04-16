#pragma once

#include "TreeRoot/Layer.h"

namespace tr
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiFrameBegin();
		virtual void OnImGuiRender() override;
		virtual void OnImGuiFrameEnd();
	private:
		float m_Time = 0.0f;
	};

}


