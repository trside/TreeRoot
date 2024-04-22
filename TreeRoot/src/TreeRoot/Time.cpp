#include "trpch.h"
#include "Time.h"

#include "TreeRoot/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTime.h"

namespace tr {

    Time* Time::Create()
    {
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLTime();
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
    }

}
