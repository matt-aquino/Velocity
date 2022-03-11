#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Platform/OpenGL/Shaders/Shader.h"

namespace Velocity
{
	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& camera); // Get scene parameters
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};

		static SceneData* m_SceneData;
	};
}