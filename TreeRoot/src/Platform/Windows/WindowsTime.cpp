#include "trpch.h"
#include "WindowsTime.h"

namespace tr {

    Ref<Time> Time::Create()
    {
        return std::make_shared<WindowsTime>();
    }

    void WindowsTime::UpdateDeltaTime()
    {
        m_DeltaTime = GetTime() - m_LastFrameTime;
        m_LastFrameTime = GetTime();
    }
}
