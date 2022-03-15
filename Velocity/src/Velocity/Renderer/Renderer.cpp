#include "vlpch.h"
#include "Renderer.h"
#include "entt.hpp"
#include "Velocity/Core/Components/Components3D.h"

namespace Velocity
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjMatrix = camera.GetViewProjectionMatrix();
	}
	
	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(entt::registry& sceneRegistry, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("uViewProj", m_SceneData->ViewProjMatrix);

		auto view = sceneRegistry.view<MeshComponent>();

		for (entt::entity entity : view)
		{
			MeshComponent comp = sceneRegistry.get<MeshComponent>(entity);
			TransformComponent transform = sceneRegistry.get<TransformComponent>(entity);

			shader->UploadUniformMat4("uModelMat", transform);
			RenderCommand::DrawIndexed(comp.m_Mesh.BindMesh());
			
			comp.m_Mesh.UnbindMesh();
		}
	}
}