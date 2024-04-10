#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern tr::Application* tr::CreateApplication();

int main(int argc, char** argv)
{
	tr::Log::Init();
	TR_CORE_WARN("ruaaaa!");
	TR_ERROR("nooooo");
	TR_INFO("hello");

	auto app = tr::CreateApplication();
	app->Run();
	delete app;
}

#endif
