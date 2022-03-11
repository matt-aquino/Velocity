#include "vlpch.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Input.h"
#include "KeyCodes.h"

#include <GLFW/glfw3.h>

namespace Velocity
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		VL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Velocity::Window>(Velocity::Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

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

			if (Input::IsKeyPressed(VL_KEY_ESCAPE))
				m_Running = false;

			// update all our layers
			for (Velocity::Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

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

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

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