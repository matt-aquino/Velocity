#include <Velocity.h>

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