#pragma once

namespace tr {

	enum class RendererAPI
	{
		None = 0, OpenGL
	};

	class Renderer
	{
	public:
		static inline RendererAPI GetCurrentAPI() { return s_RendererAPI; }
		static void SetAPI(RendererAPI api);
	private:
		static RendererAPI s_RendererAPI;
	};

}