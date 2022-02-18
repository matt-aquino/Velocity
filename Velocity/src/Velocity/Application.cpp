#include "vlpch.h"
#include "Application.h"
#include "Velocity/Events/AppEvent.h"

namespace Velocity
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}