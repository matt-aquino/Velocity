#pragma once
#include "RendererAPI.h"

namespace Velocity
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color) 
		{ 
			s_RendererAPI->SetClearColor(color); 
		}

		inline static void Clear() 
		{ 
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{ 
			s_RendererAPI->DrawIndexed(vertexArray);	
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static std::pair<uint32_t, uint32_t> GetWindowSize()
		{
			return s_RendererAPI->GetViewport();
		}

		inline static const char* GetGPU()
		{
			return s_RendererAPI->GetGPU();
		}
		
		inline static std::pair<const char*, const char*> GetAPIVersion()
		{
			switch (s_RendererAPI->GetAPI())
			{
			case RendererAPI::API::OPENGL:
				return { "OpenGL", s_RendererAPI->GetAPIVersion() };
			}

			return {"None", "N/A"};
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}
