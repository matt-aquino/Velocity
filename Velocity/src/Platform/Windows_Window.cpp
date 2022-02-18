#include "vlpch.h"
#include "Windows_Window.h"

namespace Velocity
{
	static bool s_IsGLFWInit = false;

	Window* Window::Create(const WindowProperties& props)
	{
		return new Windows_Window(props);
	}

	Windows_Window::Windows_Window(const WindowProperties& props)
	{
		Init(props);
	}

	Windows_Window::~Windows_Window()
	{
		Shutdown();
	}

	void Windows_Window::Init(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		VL_CORE_INFO("Creating Application {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_IsGLFWInit)
		{
			int success = glfwInit();
			VL_CORE_ASSERT(success, "Could not initialize GLFW!");
			s_IsGLFWInit = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void Windows_Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Windows_Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Windows_Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool Windows_Window::IsVSync() const
	{
		return m_Data.VSync;
	}
}