#include "vlpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Velocity
{
	Shader* Shader::Create(std::string& vertSrc, std::string& fragSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return new OpenGLShader(vertSrc, fragSrc);

		case RendererAPI::API::NONE:
			VL_CORE_ERROR("No API Selected!");
			return nullptr;

		case RendererAPI::API::DIRECTX:
		case RendererAPI::API::VULKAN:
		case RendererAPI::API::METAL:
			VL_CORE_ASSERT(false, "API currently not supported!");
			return nullptr;
		}

		VL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}