#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern tr::Application* tr::CreateApplication();

int main(int argc, char** argv)
{
	tr::Log::Init();
	TR_INFO("hello");
	TR_ERROR("nooooo");
	TR_CORE_WARN("ruaaaa!");

	auto app = tr::CreateApplication();
	app->Run();
	delete app;
}

#endif
