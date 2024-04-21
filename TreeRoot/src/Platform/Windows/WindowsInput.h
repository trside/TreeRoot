#pragma once

#include "TreeRoot/Input.h"

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
		static std::unique_ptr<std::unordered_map<int, bool>> KeyDownTriggered;
		static std::unique_ptr<std::unordered_map<int, bool>> KeyUpTriggered;

		static std::unique_ptr<std::unordered_map<int, bool>> MouseButtonDownTriggered;
		static std::unique_ptr<std::unordered_map<int, bool>> MouseButtonUpTriggered;
	};


}


