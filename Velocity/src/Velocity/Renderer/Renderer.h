#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Velocity
{
	class Renderer
	{
	public:
		static void Init();
		static void ResizeWindow(uint32_t width, uint32_t height);
		static std::pair<uint32_t, uint32_t> GetWindowSize();

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