#include <TreeRoot.h>

class ExampleLayer : public tr::Layer
{
public:
	ExampleLayer()
		:Layer("Example") {}

	virtual void OnUpdate() override
	{
	}

	virtual void OnEvent(tr::Event& e) override
	{
		//TR_TRACE("{0}", e);
	}

	virtual void OnImGuiRender() override
	{
	}
};

class Sandbox : public tr::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

tr::Application* tr::CreateApplication()
{
	return new Sandbox;
}

