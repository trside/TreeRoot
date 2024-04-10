#pragma once

#include "TreeRoot/Core.h"
#include "TreeRoot/Events/Event.h"

namespace tr {

	class TR_API Layer
	{
	public:
		Layer(const std::string& debugname = "Layer");

		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}	// 每层的事件处理

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}


