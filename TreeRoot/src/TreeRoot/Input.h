#pragma once

#include "trpch.h"

#include "TreeRoot/Core.h"

#include "TreeRoot/KeyCodes.h"
#include "TreeRoot/MouseButtonCodes.h"

namespace tr {

	class TR_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { auto [x, y] = s_Instance->GetMousePositionImpl(); return x; }
		inline static float GetMouseY() { auto [x, y] = s_Instance->GetMousePositionImpl(); return y; }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;

		virtual std::pair<float, float> GetMousePositionImpl() const = 0;

		static Input* s_Instance;
	};


}