#include "vlpch.h"
#include "Windows_Window.h"
#include "Velocity/Events/AppEvent.h"
#include "Velocity/Events/MouseEvent.h"
#include "Velocity/Events/KeyEvent.h"
#include "glad/glad.h"

#include "Velocity/ImGui/ImGuiGLFW.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace Velocity
{
	static bool s_IsGLFWInit = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		VL_CORE_ERROR("GLFW ERROR ({0}) : {1}", error, desc);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_IsGLFWInit = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VL_CORE_ASSERT(status, "Failed to initialize Glad!");
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		// set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(data.Width, data.Height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});
	}

	void Windows_Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Windows_Window::OnUpdate()
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
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