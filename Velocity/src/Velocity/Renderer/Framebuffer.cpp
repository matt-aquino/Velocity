#include "vlpch.h"
#include "Framebuffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Velocity
{
	Velocity::Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecs& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL: return CreateRef<OpenGLFramebuffer>(spec);

			case RendererAPI::API::VULKAN:
			case RendererAPI::API::DIRECTX:
			case RendererAPI::API::METAL:
			case RendererAPI::API::GLES:
				VL_CORE_ASSERT(false, "Renderer API currently not supported");
				return nullptr;

			case RendererAPI::API::NONE:
				VL_CORE_ASSERT(false, "No Renderer API selected");
				return nullptr;
		}

		VL_CORE_ASSERT(false, "No Renderer API selected");
		return nullptr;
	}
}