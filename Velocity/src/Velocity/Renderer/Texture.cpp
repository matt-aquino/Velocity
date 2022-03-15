#include "vlpch.h"
#include "Texture.h"
#include "Renderer.h"

// rendering APIs
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Velocity
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::NONE: VL_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
			case RendererAPI::API::OPENGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		VL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}


	Ref<Texture3D> Texture3D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: VL_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
		case RendererAPI::API::OPENGL: return std::make_shared<OpenGLTexture3D>(path);
		}

		VL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}


	Ref<Cubemap> Cubemap::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE: VL_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
		case RendererAPI::API::OPENGL: return std::make_shared<OpenGLCubemap>(path);
		}

		VL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}


}