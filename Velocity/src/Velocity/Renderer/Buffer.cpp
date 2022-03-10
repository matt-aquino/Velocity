#include "vlpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Velocity
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OPENGL:
				return new OpenGLVertexBuffer(vertices, size);

			case RendererAPI::NONE:
				VL_CORE_ERROR("No API Selected!");
				return nullptr;

			case RendererAPI::DIRECTX:
			case RendererAPI::VULKAN:
			case RendererAPI::METAL:
				VL_CORE_ASSERT(false, "API currently not supported!");
				return nullptr;
		}

		VL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OPENGL:
				return new OpenGLIndexBuffer(indices, count);

			case RendererAPI::NONE:
				VL_CORE_ERROR("No API Selected!");
				return nullptr;

			case RendererAPI::DIRECTX:
			case RendererAPI::VULKAN:
			case RendererAPI::METAL:
				VL_CORE_ASSERT(false, "API currently not supported!");
				return nullptr;
		}

		VL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}