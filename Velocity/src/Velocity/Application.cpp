#include "Application.h"
#include <stdio.h>
#include "Velocity/Events/AppEvent.h"
#include "Velocity/Log.h"

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
		WindowResizeEvent ev(1280, 700);
		VL_TRACE(ev);

		while (true);
	}
}