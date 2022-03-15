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

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glFrontFace(GL_CCW); // set counterclockwise winding order; set by default, but i want to be explicit
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // set backface culling
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Velocity::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
