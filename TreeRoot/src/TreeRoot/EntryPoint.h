#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern tr::Application* tr::CreateApplication();

int main(int argc, char** argv)
{
	auto app = tr::CreateApplication();
	app->Run();
	delete app;
}
#endif // TR_PLATFORM_WINDOWS
