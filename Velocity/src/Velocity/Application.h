#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Velocity
{

	class VELOCITY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};


	Application* CreateApplication();
}
