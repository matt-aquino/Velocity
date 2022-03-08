#include <Velocity.h>

class ExampleLayer : public Velocity::Layer
{
public:
	ExampleLayer() : Layer("Example") {}
	
	void OnUpdate() override
	{
		VL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Velocity::Event& event) override
	{
		VL_TRACE("{0}", event);
	}
};

class Sandbox : public Velocity::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{

	}
};

Velocity::Application* Velocity::CreateApplication()
{
	return new Sandbox();
}