#pragma once

#include "Core.h"

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
