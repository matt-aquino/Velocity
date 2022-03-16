#include "vlpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace Velocity
{
	void OpenGLRendererAPI::Init()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glFrontFace(GL_CCW); // set counterclockwise winding order; set by default, but i want to be explicit
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); // set backface culling
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	std::pair<uint32_t, uint32_t> OpenGLRendererAPI::GetViewport()
	{
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		return std::pair<uint32_t, uint32_t>(viewport[2], viewport[3]);
	}

}