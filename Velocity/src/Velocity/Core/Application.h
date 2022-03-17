#pragma once

#include "Velocity/Core/Core.h"
#include "Velocity/Core/Layers/LayerStack.h"
#include "Velocity/Events/Event.h"
#include "Velocity/Events/AppEvent.h"
#include "Velocity/Core/Window.h"
#include "Velocity/ImGui/ImGuiLayer.h"

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
