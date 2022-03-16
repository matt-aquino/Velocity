#pragma once

#include "Core/Core.h"
#include "Core/Layers/LayerStack.h"
#include "Events/Event.h"
#include "Events/AppEvent.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"

namespace Velocity
{
	class VELOCITY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		// Layers
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_AppMinimized = false;
		LayerStack m_LayerStack;

		static Application* s_Instance;

		float deltaTime = 0.0f;
		float lastTime = 0.0f;
	};


	Application* CreateApplication();
}
