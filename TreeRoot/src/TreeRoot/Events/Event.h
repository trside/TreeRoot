#pragma once

#include <TreeRoot/Core/Core.h>

namespace tr {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory	// 事件筛选
	{
		None = 0,
		EventCategoryApplication =		BIT(0),
		EventCategoryInput =			BIT(1),
		EventCategoryKeyboard =			BIT(2),
		EventCategoryMouse =			BIT(3),
		EventCategoryMouseButton =		BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool Handled = false;
	};

	class EventDispatcher		// 基于事件类型的事件处理器
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		using EventFun = std::function<bool(T&)>;

		template<typename T>
		bool Dispatch(EventFun<T> func)		// func为事件回调函数指针
		{
			if (m_Event.GetEventType() == T::GetStaticType())	// 判断传入的事件回调函数是否与**该dispatch函数**需要处理的事件类型相符合
			{
				m_Event.Handled = func(*(T*)&m_Event);	// *(T*)将m_Event的类型从Event*强转成T	|	将在此处进行事件处理
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& output, const Event& e)
	{
		return output << e.ToString();
	}
}

