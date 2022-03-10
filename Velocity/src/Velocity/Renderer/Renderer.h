#pragma once
#include "RenderCommand.h"

namespace Velocity
{
	class Renderer
	{
	public:

		static void BeginScene(); // Get scene parameters
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}