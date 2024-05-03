#include <TreeRoot.h>

// EntryPoint
#include <TreeRoot/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2DLayer.h"

class Sandbox : public tr::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2DLayer());
	}
	~Sandbox()
	{

	}
};

tr::Application* tr::CreateApplication()
{
	return new Sandbox;
}

