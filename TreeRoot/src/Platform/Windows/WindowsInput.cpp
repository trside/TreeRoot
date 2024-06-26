#include "trpch.h"
#include "WindowsInput.h"

#include "TreeRoot/Core/Application.h"
#include <GLFW/glfw3.h>

namespace tr {

	Input* Input::s_Instance = new WindowsInput();

	Scope<std::unordered_map<int, bool>> WindowsInput::KeyDownFlags = std::make_unique<std::unordered_map<int, bool>>();
	Scope<std::unordered_map<int, bool>> WindowsInput::KeyUpFlags = std::make_unique<std::unordered_map<int, bool>>();

	Scope<std::unordered_map<int, bool>> WindowsInput::MouseButtonDownFlags = std::make_unique<std::unordered_map<int, bool>>();
	Scope<std::unordered_map<int, bool>> WindowsInput::MouseButtonUpFlags = std::make_unique<std::unordered_map<int, bool>>();

	bool WindowsInput::GetKeyImpl(int keycode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());	// static_cast在编译时会进行类型确认，比强制转换更安全
		auto state = glfwGetKey(window, keycode);

		auto* keyDowned = KeyDownFlags.get();
		(*keyDowned)[keycode] = state == GLFW_PRESS || state == GLFW_REPEAT;

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::GetKeyDownImpl(int keycode) const
	{
		auto* keyDowned = KeyDownFlags.get();

		if (keyDowned->find(keycode) != keyDowned->end())		// if exist
		{
			if ((*keyDowned)[keycode] == true)
			{
				return false;
			}
			return (*keyDowned)[keycode] = GetKeyImpl(keycode);
		}
		return (*keyDowned)[keycode] = GetKeyImpl(keycode);
	}

	bool WindowsInput::GetKeyUpImpl(int keycode) const
	{
		auto* keyUpped = KeyUpFlags.get();

		if (keyUpped->find(keycode) != keyUpped->end())
		{
			if ((*keyUpped)[keycode] == true)
			{
				return false;
			}
			return (*keyUpped)[keycode] = !GetKeyImpl(keycode);
		}
		(*keyUpped)[keycode] = !GetKeyImpl(keycode);

		auto* keyDowned = KeyDownFlags.get();
		return (*keyDowned)[keycode] && !(*keyUpped)[keycode];
	}

	bool WindowsInput::GetMouseButtonImpl(int button) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		auto* buttonDowned = MouseButtonDownFlags.get();
		(*buttonDowned)[button] = state == GLFW_PRESS;

		return state == GLFW_PRESS;
	}

	bool WindowsInput::GetMouseButtonDownImpl(int button) const
	{
		auto* buttonDowned = MouseButtonDownFlags.get();

		if (buttonDowned->find(button) != buttonDowned->end())
		{
			if ((*buttonDowned)[button] == true)
			{
				return false;
			}
			return (*buttonDowned)[button] = GetMouseButtonImpl(button);
		}
		return (*buttonDowned)[button] = GetMouseButtonImpl(button);
	}

	bool WindowsInput::GetMouseButtonUpImpl(int button) const
	{
		auto* buttonUpped = MouseButtonUpFlags.get();

		if (buttonUpped->find(button) != buttonUpped->end())
		{
			if ((*buttonUpped)[button] == true)
			{
				return false;
			}
			return (*buttonUpped)[button] = !GetMouseButtonImpl(button);
		}
		(*buttonUpped)[button] = !GetMouseButtonImpl(button);

		auto* buttonDowned = MouseButtonDownFlags.get();
		return (*buttonDowned)[button] && !(*buttonUpped)[button];
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	void WindowsInput::OnUpdateImpl() const
	{
		auto* keyDowned = KeyDownFlags.get();
		for (auto it = keyDowned->begin(); it != keyDowned->end(); it++)
		{	
			if (it->second == true && GetKeyImpl(it->first) == false)
				it->second = false;
		}
		auto* keyUpped = KeyUpFlags.get();
		for (auto it = keyUpped->begin(); it != keyUpped->end(); it++)
		{
			if (it->second == true && GetKeyImpl(it->first) == true)
				it->second = false;
		}
		auto* buttonDowned = MouseButtonDownFlags.get();
		for (auto it = buttonDowned->begin(); it != buttonDowned->end(); it++)
		{
			if (it->second == true && GetMouseButtonImpl(it->first) == false)
				it->second = false;
		}
		auto* buttonUpped = MouseButtonUpFlags.get();
		for (auto it = buttonUpped->begin(); it != buttonUpped->end(); it++)
		{
			if (it->second == true && GetMouseButtonImpl(it->first) == true)
				it->second = false;
		}
	}
}