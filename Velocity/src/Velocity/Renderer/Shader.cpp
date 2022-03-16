#include "vlpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Velocity
{
	Ref<Shader> Shader::Create(const std::string& name, std::string& vertSrc, std::string& fragSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return std::make_shared<OpenGLShader>(name, vertSrc, fragSrc);

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

	
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OPENGL:
			return std::make_shared<OpenGLShader>(path);

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



	
	void ShaderLibrary::AddShader(const std::string& name, const Ref<Shader>& shader)
	{
		VL_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::AddShader(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		AddShader(name, shader);
	}	

	Ref<Shader> ShaderLibrary::LoadShader(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		AddShader(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::LoadShader(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		AddShader(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		VL_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}
}