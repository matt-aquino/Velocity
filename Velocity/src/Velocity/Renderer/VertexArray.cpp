#include "vlpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Velocity
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE: VL_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
		case RendererAPI::OPENGL: return new OpenGLVertexArray();
		}

		VL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}