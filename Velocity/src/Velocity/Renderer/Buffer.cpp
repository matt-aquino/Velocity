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
			case RendererAPI::API::OPENGL:
				return new OpenGLVertexBuffer(vertices, size);

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

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OPENGL:
				return new OpenGLIndexBuffer(indices, count);

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