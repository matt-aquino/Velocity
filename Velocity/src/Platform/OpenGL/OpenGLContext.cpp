#include "vlpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <gl/GL.h>

Velocity::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	VL_CORE_ASSERT(windowHandle, "Window Handle is NULL!");
}

void Velocity::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	VL_CORE_ASSERT(status, "Failed to initialize Glad!");

	glClearColor(0.3, 0.3, 0.3, 1.0);
}

void Velocity::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
