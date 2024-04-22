#include "trpch.h"
#include "OpenGLTime.h"

namespace tr {

    void OpenGLTime::CalculateDeltaTime()
    {
        m_DeltaTime = GetTime() - m_LastFrameTime;
        m_LastFrameTime = GetTime();
    }
}
