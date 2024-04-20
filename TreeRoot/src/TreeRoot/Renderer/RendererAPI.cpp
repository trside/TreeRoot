#include "trpch.h"
#include "RendererAPI.h"

namespace tr {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;		// 私有静态成员在类外需要通过类限定符访问

}
