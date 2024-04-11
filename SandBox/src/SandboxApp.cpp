#include <TreeRoot.h>

class ExampleLayer : public tr::Layer
{
public:
	ExampleLayer()
		:Layer("Example") {}

	void OnUpdate() override
	{
	}

	void OnEvent(tr::Event& e) override
	{
		//TR_TRACE("{0}", e);
	}
};

class Sandbox : public tr::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new tr::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

tr::Application* tr::CreateApplication()
{
	return new Sandbox;
}

