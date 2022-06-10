#include "vlpch.h"
#include "Application.h"
#include "Velocity/Renderer/Renderer.h"
#include "Velocity/Input/Input.h"
#include "Velocity/Input/KeyCodes.h"

#include <GLFW/glfw3.h>

namespace Velocity
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		VL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Scope<Velocity::Window>(Velocity::Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			deltaTime = time - lastTime;
			lastTime = time;

			if (!m_AppMinimized)
			{
				// update all our layers
				for (Velocity::Layer* layer : m_LayerStack)
					layer->OnUpdate(deltaTime);
			}

			// begin rendering our ImGui overlay
			m_ImGuiLayer->Begin();

			// if any layers render to ImGui, render them
			for (Velocity::Layer* layer : m_LayerStack)
				layer->OnImGuiRender(deltaTime);

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		unsigned int width = e.GetWidth(), height = e.GetHeight();

		if (width == 0 || height == 0)
		{
			m_AppMinimized = true;
			return false;
		}

		m_AppMinimized = false;

		Renderer::ResizeWindow(width, height);

		return false;
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose)); // allows application to close by hitting the window button
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
	
}