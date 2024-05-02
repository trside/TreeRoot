#pragma once

#include "trpch.h"

#include "TreeRoot/Core/Core.h"

#include "TreeRoot/Core/KeyCodes.h"
#include "TreeRoot/Core/MouseButtonCodes.h"

namespace tr {

	class Input
	{
	public:
		inline static bool GetKey(int keycode) { return s_Instance->GetKeyImpl(keycode); }
		inline static bool GetKeyDown(int keycode) { return s_Instance->GetKeyDownImpl(keycode); }
		inline static bool GetKeyUp(int keycode) { return s_Instance->GetKeyUpImpl(keycode); }

		inline static bool GetMouseButton(int button) { return s_Instance->GetMouseButtonImpl(button); }
		inline static bool GetMouseButtonDown(int button) { return s_Instance->GetMouseButtonDownImpl(button); }
		inline static bool GetMouseButtonUp(int button) { return s_Instance->GetMouseButtonUpImpl(button); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { auto [x, y] = s_Instance->GetMousePositionImpl(); return x; }
		inline static float GetMouseY() { auto [x, y] = s_Instance->GetMousePositionImpl(); return y; }

		inline static void OnUpdate() { return s_Instance->OnUpdateImpl(); }
	protected:
		virtual bool GetKeyImpl(int keycode) const = 0;
		virtual bool GetKeyDownImpl(int keycode) const = 0;
		virtual bool GetKeyUpImpl(int keycode) const = 0;

		virtual bool GetMouseButtonImpl(int button) const = 0;
		virtual bool GetMouseButtonDownImpl(int button) const = 0;
		virtual bool GetMouseButtonUpImpl(int button) const = 0;

		virtual std::pair<float, float> GetMousePositionImpl() const = 0;

		virtual void OnUpdateImpl() const = 0;

		static Input* s_Instance;
	};


}