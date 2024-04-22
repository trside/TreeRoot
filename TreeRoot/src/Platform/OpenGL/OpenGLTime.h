#pragma once

#include "TreeRoot/Time.h"

#include <GLFW/glfw3.h>

namespace tr {

	class OpenGLTime : public Time
	{
	public:
		virtual ~OpenGLTime() {}

		virtual inline float GetTime() const override { return (float)glfwGetTime(); }
		virtual inline float GetDeltaTime() const override { return m_DeltaTime; }

		virtual void CalculateDeltaTime() override;
	private:
		float m_LastFrameTime = 0.0f;
		float m_DeltaTime = 0.0f;
	};

}