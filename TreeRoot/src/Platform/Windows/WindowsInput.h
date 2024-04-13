#pragma once

#include "TreeRoot/Input.h"

namespace tr {

	class WindowsInput : public Input
	{
		virtual bool IsKeyPressedImpl(int keycode) const override;
		virtual bool IsMouseButtonPressedImpl(int button) const override;

		virtual std::pair<float, float> GetMousePositionImpl() const override;
	};


}


