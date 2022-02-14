#include "Application.h"
#include <stdio.h>

namespace Velocity
{
	Application::Application()
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
			printf("\rWelcome To Velocity!");
	}
}