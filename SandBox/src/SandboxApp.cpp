#include <TreeRoot.h>


class Sandbox : public tr::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

tr::Application* tr::CreateApplication()
{
	return new Sandbox;
}

