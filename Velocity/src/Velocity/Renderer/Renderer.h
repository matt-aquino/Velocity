#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Velocity
{
	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& camera); // Get scene parameters
		static void BeginScene(PerspectiveCamera& camera); // Get scene parameters
		static void EndScene();
		static void Submit(entt::registry& sceneRegistry, const Ref<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};

		static SceneData* m_SceneData;
	};
}