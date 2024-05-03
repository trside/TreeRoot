#pragma once

#include "TreeRoot/Core/Input.h"

namespace tr {

	class WindowsInput : public Input
	{
	public:
		virtual bool GetKeyImpl(int keycode) const override;
		virtual bool GetKeyDownImpl(int keycode) const override;
		virtual bool GetKeyUpImpl(int keycode) const override;

		virtual bool GetMouseButtonImpl(int button) const override;
		virtual bool GetMouseButtonDownImpl(int button) const override;
		virtual bool GetMouseButtonUpImpl(int button) const override;

		virtual std::pair<float, float> GetMousePositionImpl() const override;

		virtual void OnUpdateImpl() const override;
	private:
		static Scope<std::unordered_map<int, bool>> KeyDownFlags;
		static Scope<std::unordered_map<int, bool>> KeyUpFlags;

		static Scope<std::unordered_map<int, bool>> MouseButtonDownFlags;
		static Scope<std::unordered_map<int, bool>> MouseButtonUpFlags;
	};


}


