#pragma once
#include "Velocity/Window.h"
#include "GLFW/glfw3.h"

namespace Velocity
{
	class Windows_Window : public Window
	{
	public:
		Windows_Window(const WindowProperties& props);
		virtual ~Windows_Window();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline GLFWwindow& GetWindow() const override { return *m_Window; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;
		
		struct WindowData
		{
			std::string Title = "";
			unsigned int Width = 0, Height = 0;
			bool VSync = true;
			EventCallbackFn EventCallback = nullptr;
		};

		WindowData m_Data;
	};
}